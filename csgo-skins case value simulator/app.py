import subprocess
import sys
import time
import socket
import shutil
import os
from pathlib import Path
from playwright.sync_api import sync_playwright
from bs4 import BeautifulSoup
from collections import defaultdict

REMOTE_DEBUGGING_PORT = 9222

CHROME_PATH = None

USER_DATA_DIR = str(Path.cwd() / "chrome_debug_profile")

OPEN_URL = "about:blank"

OUT_FILE = "page.html"

def find_chrome_executable():
    if CHROME_PATH:
        return CHROME_PATH
    # Common candidates
    candidates = []
    if sys.platform.startswith("win"):
        candidates += [
            r"C:\Program Files\Google\Chrome\Application\chrome.exe",
            r"C:\Program Files (x86)\Google\Chrome\Application\chrome.exe",
        ]
    elif sys.platform == "darwin":
        candidates += [
            "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome",
            "/Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome",
        ]
    else:  # linux-ish
        candidates += ["/usr/bin/google-chrome", "/usr/bin/chromium-browser", "/usr/bin/chromium"]
    # try candidates and PATH
    for c in candidates:
        if shutil.which(c) or Path(c).exists():
            return c
    # try PATH lookup by common names
    for name in ("google-chrome", "chrome", "chromium", "chromium-browser", "google-chrome-stable"):
        p = shutil.which(name)
        if p:
            return p
    return None

def wait_port(host: str, port: int, timeout: float = 10.0):
    """Wait until host:port accepts TCP connections or timeout (seconds)."""
    deadline = time.time() + timeout
    while time.time() < deadline:
        try:
            with socket.create_connection((host, port), timeout=1):
                return True
        except OSError:
            time.sleep(0.2)
    return False

def launch_chrome(chrome_path: str, user_data_dir: str, remote_port: int, open_url: str = "about:blank"):
    # Ensure user data dir exists
    Path(user_data_dir).mkdir(parents=True, exist_ok=True)

    args = [
        chrome_path,
        f"--remote-debugging-port={remote_port}",
        f"--user-data-dir={user_data_dir}",
        "--no-first-run",
        "--disable-extensions",
        "--disable-default-apps",
        # optionally open a new window/tab with a URL:
        open_url,
    ]

    # On macOS there are spaces in the path; that's fine when using args list.
    print("Starting Chrome with command:")
    print(" ".join(args))
    # Start Chrome detached so our Python process can continue. Keep the process handle in case we want to kill it.
    proc = subprocess.Popen(args, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return proc

def attach_and_capture(remote_port: int, out_file: str, url_substring: str | None = None):
    # Connect over CDP using Playwright
    with sync_playwright() as p:
        print("Connecting to running Chrome via CDP...")
        browser = p.chromium.connect_over_cdp(f"http://localhost:{remote_port}")
        # Playwright may expose contexts/pages via browser.pages or browser.contexts
        pages = []
        try:
            # prefer browser.pages
            pages = browser.pages
        except Exception:
            pages = []
        if not pages:
            # try contexts[0].pages
            contexts = browser.contexts
            if contexts:
                pages = contexts[0].pages
        if not pages:
            print("No pages found. If you have tabs open, try again after opening one.")
            browser.close()
            return

        chosen = None
        if url_substring:
            for pg in pages:
                try:
                    if url_substring in pg.url:
                        chosen = pg
                        break
                except Exception:
                    continue
        if chosen is None:
            chosen = pages[0]

        print("Attaching to tab with URL:", chosen.url)
        # give JS a moment to settle
        time.sleep(0.5)
        html = chosen.content()
        with open(out_file, "w", encoding="utf-8") as f:
            f.write(html)
        print("Saved page HTML to", out_file)
        # close only the connection to remote; not the Chrome process itself
        browser.close()

def case_value_estimator(file_name: str, num_items: int = 100_000):
    print("Starting case value estimator...")

    # Read HTML
    with open(OUT_FILE, encoding="utf-8") as f:
        html = f.read()

    soup = BeautifulSoup(html, "html.parser")

    # Extract case name
    case_name_tag = soup.select("h1.AppPage_title")
    case_name = case_name_tag[0].text.strip() if case_name_tag else "Case name not found"
    case_price_tag = soup.select("div.ContainerPrice")
    case_price = case_price_tag[0].text.strip() if case_price_tag else "Case price not found"

    # Extract all items
    items = soup.select("div.ContainerGroupedItem")
    case_data = []

    for item in items:
        name_tag = item.select_one("h3.ContainerGroupedItem_name")
        if not name_tag:
            continue
        name = name_tag.text.strip()

        rows = item.select("table.chances_table tbody tr")
        for row in rows:
            cols = row.find_all("td")
            if len(cols) < 4:
                continue

            rarity = cols[0].text.strip()
            price_text = cols[1].text.strip().replace("$", "")
            try:
                price = float(price_text)
            except ValueError:
                price = None
            value_range = cols[2].text.strip()
            odds_text = cols[3].text.strip().replace("%", "")
            try:
                odds = float(odds_text)/100
            except ValueError:
                odds = None

            case_data.append({
                "name": name,
                "rarity": rarity,
                "price": price,
                "range": value_range,
                "odds": odds
            })

    if not case_data:
        print("No case data found.")
        return

    # Extract prices and odds
    prices = [d["price"] for d in case_data if d["price"] is not None]
    odds = [d["odds"] for d in case_data if d["odds"] is not None]

    # Best/worst price
    best_price = max(prices)
    worst_price = min(prices)

    # Expected value per item
    expected_value = sum(d["price"] * d["odds"] for d in case_data if d["price"] is not None and d["odds"] is not None)

    # Average price for naive buy approach
    avg_price = sum(prices)/len(prices)

    # Buying N items
    total_spent = num_items * avg_price
    total_ev = num_items * expected_value
    money_lost = total_spent - total_ev
    lose_percentage = 100 * money_lost / total_spent
    keep_percentage = 100 - lose_percentage

    # EV per rarity
    rarity_ev = defaultdict(float)
    for d in case_data:
        if d["price"] is not None and d["odds"] is not None:
            rarity_ev[d["rarity"]] += d["price"] * d["odds"]

    # Save all info to file
    if not file_name.endswith(".txt"):
        file_name += ".txt"
    with open(file_name, "w", encoding="utf-8") as f:
        f.write(f"Case name: {case_name}\n")
        f.write(f"Case price: {case_price}\n")
        f.write(f"Best item price: ${best_price:.2f}\n")
        f.write(f"Worst item price: ${worst_price:.2f}\n")
        f.write(f"Expected value per item: ${expected_value:.4f}\n\n")

        f.write(f"Buying {num_items} items:\n")
        f.write(f"  Total money spent (average price approach): ${total_spent:.2f}\n")
        f.write(f"  Estimated total value (EV): ${total_ev:.2f}\n")
        f.write(f"  Estimated money lost: ${money_lost:.2f}\n")
        f.write(f"  Lose percentage: {lose_percentage:.2f}%\n")
        f.write(f"  Keep percentage: {keep_percentage:.2f}%\n\n")

        f.write("Expected value per rarity:\n")
        for r, ev in rarity_ev.items():
            f.write(f"  {r}: ${ev:.4f}\n")

        f.write("\nItems inside case:\n")
        for entry in case_data:
            f.write(f"{entry}\n")

    print(f"Analysis saved to '{file_name}'")

    if sys.platform.startswith("win"):
        os.startfile(file_name)

    # macOS
    elif sys.platform == "darwin":
        subprocess.run(["open", file_name])

    # Linux / most Unix
    else:
        subprocess.run(["xdg-open", file_name])


def main():
    chrome = find_chrome_executable()
    if not chrome:
        print("Chrome executable not found automatically. Set CHROME_PATH variable in the script.")
        return

    # Launch Chrome
    proc = launch_chrome(chrome, USER_DATA_DIR, REMOTE_DEBUGGING_PORT, OPEN_URL)

    # Wait for CDP port to be ready
    print(f"Waiting for Chrome remote debugging port localhost:{REMOTE_DEBUGGING_PORT} ...")
    if not wait_port("127.0.0.1", REMOTE_DEBUGGING_PORT, timeout=15.0):
        print("Timed out waiting for Chrome to open the debugging port.")
        print("You can still manually open Chrome with --remote-debugging-port and run the attach script separately.")
        return

    print("Chrome debugging port is ready. Now you can manually navigate in the opened Chrome window.")
    input("Navigate to the site and solve any verification, then press ENTER here to capture the page...")

    try:
        attach_and_capture(REMOTE_DEBUGGING_PORT, OUT_FILE, url_substring=None)
    finally:
        # optional: terminate the Chrome instance we started
        answer = input("Kill the Chrome process we launched? (y/n) [y]: ").strip().lower() or "y"
        if answer.startswith("y"):
            proc.terminate()
            print("Terminated Chrome process.")
        answer = input("Apply CSGO-SKINS case value estimator? (y/n) [y]: ")
        if answer.startswith("y"):
            file_name = input("Alright, name of file to store data: ")
            case_value_estimator(file_name)

if __name__ == "__main__":
    main()