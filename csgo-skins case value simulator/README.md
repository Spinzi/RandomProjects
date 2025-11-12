# CSGO Case Value Estimator

A simple Python tool that lets you **analyze the value of CSGO cases** by scraping the case page and calculating the **expected value (EV)** of opening items.

It uses **Playwright** to connect to a running Chrome instance, captures the page's HTML, and estimates how much money is lost or kept when opening cases.

---

## 🧩 Features
- Automatically finds and launches Google Chrome.
- Connects via remote debugging.
- Captures the full HTML of a CSGO case page.
- Parses item rarities, prices, and odds.
- Calculates:
  - Expected value per case
  - Best and worst item
  - Total losses or profits after many openings
- Saves results to a text file.

---

## 🚀 How to Use

### 🖥 If you have the **EXE version**
1. Just run the `.exe` file.
2. Chrome will open automatically.
3. Navigate manually to the CSGO case page you want.
4. Once the page is fully loaded, go back to the console and **press ENTER**.
5. The program will capture the page and analyze it.
6. You’ll be asked if you want to:
   - Close Chrome.
   - Run the case value estimator (choose **y**).
7. Enter a name for your output file — it will create a `.txt` with all the results.

That’s it! You don’t need to install anything else.

---

### 🐍 If you want to run the **Python source code**
#### 1️⃣ Install dependencies
```bash
pip install playwright beautifulsoup4
python -m playwright install chromium
