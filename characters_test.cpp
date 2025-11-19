#include <iostream>
#include <limits>
#include <cstring> // for strlen
using namespace std;

// === VARIABLE DECLARATIONS ===
char* test_1;                 // BAD: uninitialized pointer — unsafe to read into
char test_2[1];               // tiny array — unsafe for large input (overflow)
char* test_3 = new char[100]; // GOOD: heap array with enough space
char test_4[100];             // GOOD: stack array with enough space

int main() {
    cout << "=== MEMORY STATE BEFORE READING ===\n";

    cout << "test_1: pointer, UNINITIALIZED -> points to: " << (void*)test_1 << "\n";
    cout << "test_2: array[1] -> size 1 byte only\n";
    cout << "test_3: pointer to heap array[100] -> address: " << (void*)test_3 << "\n";
    cout << "test_4: stack array[100] -> address: " << (void*)test_4 << "\n\n";

    cout << "=== NOW ATTEMPTING READS ===\n\n";

    // ===== OPTION: Reading unsafe/uninitialized variables =====
    char choice;
    cout << "Do you want to try reading from unsafe variables test_1 and test_2? (y/n): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 'y' || choice == 'Y') {
        // 1 - BAD POINTER
        try {
            cout << "[1] Reading into test_1 (UNINITIALIZED pointer)...\n";
            cin.get(test_1, 100);   // CRASHES or undefined behavior
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        catch (...) {
            cout << "Caught exception for test_1 (this will likely never print).\n";
        }

        // 2 - TINY ARRAY
        try {
            cout << "[2] Reading into test_2 (array[1])...\n";
            cin.get(test_2, 100);   // buffer overflow / undefined behavior
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        catch (...) {
            cout << "Caught exception for test_2.\n";
        }
    }
    else {
        cout << "Skipping unsafe reads for test_1 and test_2.\n";
    }

    // ===== SAFE variables =====
    // 3 - VALID POINTER
    try {
        cout << "[3] Reading into test_3 (GOOD pointer)...\n";
        cin.get(test_3, 100);       // safe
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    catch (...) {
        cout << "Caught exception for test_3.\n";
    }

    // 4 - VALID ARRAY
    try {
        cout << "[4] Reading into test_4 (GOOD array)...\n";
        cin.get(test_4, 100);       // safe
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    catch (...) {
        cout << "Caught exception for test_4.\n";
    }

    // ===== SHOW RESULTS =====
    cout << "\n=== CONTENTS OF VARIABLES ===\n";

    cout << "test_1: ";
    if (test_1)
        cout << test_1 << "\n"; // likely crash or garbage
    else
        cout << "(pointer is uninitialized or skipped)\n";

    cout << "test_2: " << test_2 << " (length reported by strlen: " << strlen(test_2) << ")\n";
    cout << "test_3: " << test_3 << " (length: " << strlen(test_3) << ")\n";
    cout << "test_4: " << test_4 << " (length: " << strlen(test_4) << ")\n";

    cout << "\n=== PROGRAM END ===\n";

    // CLEANUP
    delete[] test_3;
}
