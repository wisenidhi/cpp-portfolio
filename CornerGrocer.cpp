// CornerGrocer.cpp : Defines the entry point for the application.
//


/*
    Corner Grocer Item Tracking Program
    CS 210 ? Project Three
    Author: Nidhi Shree

    This program reads a list of grocery items from the file
    "CS210_Project_Three_Input_File.txt". It counts how many
    times each item appears, writes the results to a backup file
    named "frequency.dat", and provides a simple menu so the user
    can view different frequency reports.
*/
#include "CornerGrocer.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

/*
    ItemTracker class
    -----------------
    Stores item frequencies in a map and provides functions to
    load data, print frequency lists, print histograms, and
    search for an individual item.
*/
class ItemTracker {
private:
    map<string, int> itemCounts;

    // Helper function to convert text to lowercase
    string toLowercase(const string& text) const {
        string result = text;
        transform(result.begin(), result.end(), result.begin(),
            [](unsigned char c) { return tolower(c); });
        return result;
    }

public:
    // Load items from input file
    bool loadData(const string& fileName) {
        ifstream inputFile(fileName);
        if (!inputFile.is_open()) {
            return false;
        }

        string item;
        while (inputFile >> item) {
            itemCounts[toLowercase(item)]++;
        }

        inputFile.close();
        return true;
    }

    // Write backup file: frequency.dat
    void writeBackup(const string& fileName) const {
        ofstream outFile(fileName);

        if (!outFile.is_open()) {
            cout << "Warning: Could not create backup file.\n";
            return;
        }

        for (const auto& entry : itemCounts) {
            outFile << entry.first << " " << entry.second << endl;
        }

        outFile.close();
    }

    // Return frequency for one item
    int getFrequency(const string& item) const {
        string key = toLowercase(item);
        if (itemCounts.find(key) != itemCounts.end()) {
            return itemCounts.at(key);
        }
        return 0;
    }

    // Print full frequency list
    void printAllFrequencies() const {
        cout << "\nAll Item Frequencies:\n";
        for (const auto& entry : itemCounts) {
            cout << entry.first << " " << entry.second << endl;
        }
        cout << endl;
    }

    // Print histogram using asterisks
    void printHistogram() const {
        cout << "\nItem Frequency Histogram:\n";
        for (const auto& entry : itemCounts) {
            cout << entry.first << " ";
            for (int i = 0; i < entry.second; i++) {
                cout << "*";
            }
            cout << endl;
        }
        cout << endl;
    }
};

// Function to show menu options
void showMenu() {
    cout << "----------------------------------\n";
    cout << " Corner Grocer - Tracking System\n";
    cout << "----------------------------------\n";
    cout << "1. Look up frequency of an item\n";
    cout << "2. Print all item frequencies\n";
    cout << "3. Print histogram of frequencies\n";
    cout << "4. Exit\n";
    cout << "Choose an option (1-4): ";
}

int main() {
    ItemTracker tracker;

    // Load data from input file
    if (!tracker.loadData("CS210_Project_Three_Input_File.txt")) {
                           //CS210_Project_Three_Input_File
        cout << "ERROR: Could not open input file.\n";
        return 1;
    }

    // Create backup file
    tracker.writeBackup("frequency.dat");

    int choice = 0;

    while (choice != 4) {
        showMenu();
        cin >> choice;

        // Input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(500, '\n');
            cout << "Please enter a number between 1 and 4.\n\n";
            continue;
        }

        if (choice == 1) {
            string item;
            cout << "Enter item name: ";
            cin >> item;

            int freq = tracker.getFrequency(item);
            cout << "Frequency of " << item << ": " << freq << "\n\n";
        }
        else if (choice == 2) {
            tracker.printAllFrequencies();
        }
        else if (choice == 3) {
            tracker.printHistogram();
        }
        else if (choice == 4) {
            cout << "Exiting program.\n";
        }
        else {
            cout << "Invalid option. Try again.\n\n";
        }
    }

    return 0;
}

