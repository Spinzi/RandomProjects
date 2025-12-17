import customtkinter as ctk
import sounddevice as sd
import numpy as np
import tkinter as tk
import time
import ctypes
import json
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
SETTINGS_FILE = os.path.join(SCRIPT_DIR, "settings.json")

def load_settings():
    if os.path.exists(SETTINGS_FILE):
        try:
            with open(SETTINGS_FILE, "r") as f:
                return json.load(f)
        except:
            return {}
    return {}

def save_settings(settings):
    with open(SETTINGS_FILE, "w") as f:
        json.dump(settings, f)

ctypes.windll.user32.SetProcessDPIAware()

screen_width = ctypes.windll.user32.GetSystemMetrics(0)
screen_height = ctypes.windll.user32.GetSystemMetrics(1)

# --- App config ---
ctk.set_appearance_mode("dark")
ctk.set_default_color_theme("dark-blue")

# --- Main controller window ---
root = ctk.CTk()
root.title("Mic Guard Game Loop")
root.geometry("260x180+20+20")
root.attributes("-topmost", True)
root.resizable(False, False)

# Slider for “volume threshold”
threshold_slider = ctk.CTkSlider(root, from_=0, to=100)
threshold_slider.set(50)
threshold_slider.pack(pady=20)

volume_bar = ctk.CTkProgressBar(root, width=200, height=20, progress_color="green")
volume_bar.set(0)  # 0–1 scale
volume_bar.pack(pady=5)

mic_value_label = ctk.CTkLabel(root, text="CTkLabel", fg_color="transparent", font=("Arial", 16))
mic_value_label.pack()

# --- Overlay window ---
overlay = tk.Toplevel(root)
overlay.withdraw()  # hidden at start

# Remove window borders and make topmost
overlay.overrideredirect(True)
overlay.attributes("-topmost", True)

# Transparent background
overlay.configure(bg="magenta")
overlay.attributes("-transparentcolor", "magenta")
overlay.geometry(f"{screen_width}x{screen_height}+0+0")
overlay.attributes('-alpha', 0.5)

overlay_label = tk.Label(
    overlay,
    text="🎤",
    font=("Arial", 200),
    bg="magenta",
    fg="red"
)
def position_mic_icon():
    overlay.update_idletasks()
    overlay_label.place(
        relx = 1,
        rely = 1,
        anchor= "se"
    )

devices = sd.query_devices()
mic_names = []
mic_history = []

def get_smoothed_volume(raw):
    mic_history.append(raw)
    if len(mic_history) > 3:  # keep last 5 samples
        mic_history.pop(0)
    return sum(mic_history) / len(mic_history)

for d in devices:
    if d['max_input_channels'] > 0:
        name = d['name']
        # keep names with 'Microphone' or 'Mic', ignore 'Stereo', 'System', 'Wave', etc.
        if "Microphone" in name or "Mic" in name:
            if not any(x in name for x in ["Stereo", "System", "Wave"]):
                mic_names.append(name)

print(mic_names)

mic_var = ctk.StringVar(value=mic_names[0])
mic_dropdown = ctk.CTkOptionMenu(root, values=mic_names, variable=mic_var)
mic_dropdown.pack(pady=10)

def get_mic_index():
    devices = sd.query_devices()
    for i, d in enumerate(devices):
        if d['name'] == mic_var.get():
            return i
    return 0  # fallback

def get_current_volume():
    mic_index = get_mic_index()
    duration = 0.02  # 50 ms
    try:
        # record small chunk from mic
        data = sd.rec(int(duration * 44100), samplerate=44100, channels=1, dtype='float32', device=mic_index)
        sd.wait()
        rms = np.sqrt(np.mean(data**2))  # loudness
        scaled = rms * 1000  # scale to 0-100 range
        if scaled > 100:     # clamp max
            scaled = 100
        return scaled
    except Exception as e:
        millis = int(time.time() * 1000)  # current time in milliseconds
        print("Mic read error:", e, "At time:", millis)
        return -1

settings = load_settings()
saved_threshold = settings.get("threshold", 50)
saved_mic = settings.get("mic", mic_names[0])  # fallback to first mic

threshold_slider.set(saved_threshold)
mic_var = ctk.StringVar(value=saved_mic)

def on_threshold_change(value):
    settings["threshold"] = int(float(value))
    save_settings(settings)

threshold_slider.configure(command=on_threshold_change)

def on_mic_change(choice):
    settings["mic"] = choice
    save_settings(settings)

mic_dropdown.configure(command=on_mic_change)

# --- Game loop / update function ---
def game_loop():
    # Placeholder for current volume (simulate loudness)
    current_volume = get_smoothed_volume(get_current_volume()) 
    
    # Get threshold from slider
    threshold = threshold_slider.get()

    if current_volume == -1:
    
        mic_value_label.configure(text = f"Mic not working.")

        volume_bar.set(0)

    else:

        volume_bar.set(current_volume / 100)

        mic_value_label.configure(text = f"Threshold: {int(threshold)} | Volume: {int(current_volume)}")

        # Check if volume exceeds threshold
        if current_volume >= threshold:
            overlay.deiconify()
            position_mic_icon()
            volume_bar.configure(progress_color = "red")
        else:
            overlay.withdraw()
            volume_bar.configure(progress_color = "green")

    # Schedule next loop
    root.after(33, game_loop)  # ~20 updates/sec

# Start loop
game_loop()
root.mainloop()
