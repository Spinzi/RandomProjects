import os
from pyzbar.pyzbar import decode
from PIL import Image
import subprocess
import platform
import time

# ==== CONFIG ====
IMAGE_FOLDER = "images"       # Folder with all your barcode images
OUTPUT_FILE = "output.json"    # File to save JS objects

# ==== COLLECT IMAGES ====
files = sorted([f for f in os.listdir(IMAGE_FOLDER)
                if f.lower().endswith((".png", ".jpg", ".jpeg"))])

if not files:
    print("No images found in folder:", IMAGE_FOLDER)
    exit()

# ==== OPEN OUTPUT FILE ====
with open(OUTPUT_FILE, "a", encoding="utf-8") as out_file:
    for filename in files:
        path = os.path.join(IMAGE_FOLDER, filename)
        print(f"\nOpening: {filename}")

        # Open the image
        img = Image.open(path)

        if platform.system() == "Windows":
            os.startfile(path)

        # Try to decode barcode
        decoded = decode(img)
        if decoded:
            code = decoded[0].data.decode("utf-8")
            print(f"Detected barcode: {code}")
        else:
            print("⚠ Could not detect barcode automatically.")
            code = input("Enter barcode manually: ").strip()

        # Prompt for product name
        name = input("Enter product name: ").strip()

        # Append to output file
        out_file.write(f'{{ label:"{name}", code:"{code}" }},\n')

print(f"\nDone! All entries saved in {OUTPUT_FILE}")
