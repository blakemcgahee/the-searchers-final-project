#include <iostream>  // Standard library for input and output operations (like 'cout' and 'cin').
#include <vector>    // To use std::vector for your dataset
#include <string>    // To use std::string

// Include your ProjectUtils.h header here.
// This will make functions like generateAndSortDataset, loadAndSortDatasetFromFile,
// jumpSearch, and measureSearchTime available.
#include "ProjectUtils.h"

// Your main function, the entry point of your program.
int main() {
    std::cout << "Hello from the Search Algorithm Performance Study!\n";

    std::vector<int> dataset; // Declare your dataset vector here.
    const int DATASET_SIZE = 1000000; // Default size for generated data
    const int MIN_VAL = 1;            // Default min value for generated data
    const int MAX_VAL = 10000000;     // Default max value for generated data

    // Initial dataset generation (you can change this to load from file if you prefer a default)
    // For now, we'll start with a generated dataset to ensure the app can run immediately.
    ProjectUtils::generateAndSortDataset(dataset, DATASET_SIZE, MIN_VAL, MAX_VAL);

    // --- GERSON'S UI SECTION (Updated for file loading option) ---
    int choice;
    do {
        // Print menu options
        std::cout << "\n-------------------------------------------------\n";
        std::cout << "|           Search Algorithm Performance Study    |\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "| 1. Generate New Dataset                         |\n";
        std::cout << "| 2. Load Dataset from File                       |\n"; // New option
        std::cout << "| 3. Search (Jump Search)                         |\n";
        std::cout << "| 4. Search (Interpolation Search)                |\n"; // Thiago's search
        std::cout << "| 5. Exit                                         |\n"; // Updated exit option
        std::cout << "---------------------------------------------------\n";
        std::cout << "Output:\n";
        std::cout << "> Enter choice: ";
        std::cin >> choice;

        // Clear the input buffer after reading an integer choice
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            // Re-generate dataset
            ProjectUtils::generateAndSortDataset(dataset, DATASET_SIZE, MIN_VAL, MAX_VAL);
        }
        else if (choice == 2) {
            // NEW: Load dataset from file
            std::string filename;
            std::cout << "> Enter filename (e.g., data.txt): ";
            std::getline(std::cin, filename); // Read the full filename, including spaces

            if (!ProjectUtils::loadAndSortDatasetFromFile(dataset, filename)) {
                std::cout << "Failed to load dataset from file. Please check filename and content.\n";
            }
            // Ensure dataset is not empty after attempted load
            if (dataset.empty()) {
                std::cout << "Current dataset is empty. Please generate or load a valid dataset.\n";
            }
        }
        else if (choice == 3) {
            // Call Blake's Jump Search and measure time
            if (dataset.empty()) {
                std::cout << "No dataset loaded. Please generate or load a dataset first.\n";
            }
            else {
                int target;
                std::cout << "> Enter value to search: ";
                std::cin >> target;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

                int found_idx;
                long long duration_us = ProjectUtils::measureSearchTime(
                    [&](const std::vector<int>& arr, int val) { return ProjectUtils::jumpSearch(arr, val); },
                    dataset, target, found_idx
                );
                if (found_idx != -1) {
                    std::cout << "Value " << target << " found at index " << found_idx << ".\n";
                }
                else {
                    std::cout << "Value " << target << " not found.\n";
                }
                std::cout << "Jump Search Time: " << duration_us / 1000.0 << " ms\n";
            }
        }
        else if (choice == 4) {
            // Call Thiago's Interpolation Search and measure time
            if (dataset.empty()) {
                std::cout << "No dataset loaded. Please generate or load a dataset first.\n";
            }
            else {
                // Thiago will implement this part of the UI interaction and call his function.
                // Example:
                // int target;
                // std::cout << "> Enter value to search: ";
                // std::cin >> target;
                // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                // int found_idx;
                // long long duration_us = ProjectUtils::measureSearchTime(
                //     [&](const std::vector<int>& arr, int val){ return ProjectUtils::interpolationSearch(arr, val); },
                //     dataset, target, found_idx
                // );
                // if (found_idx != -1) {
                //     std::cout << "Value " << target << " found at index " << found_idx << ".\n";
                // } else {
                //     std::cout << "Value " << target << " not found.\n";
                // }
                // std::cout << "Interpolation Search Time: " << duration_us / 1000.0 << " ms\n";
                std::cout << "Interpolation Search not yet implemented. Please wait for Thiago's part.\n";
            }
        }
        else if (choice == 5) {
            std::cout << "Exiting program. Goodbye!\n";
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5); // Loop until exit choice

    return 0; // Indicate successful execution
}
