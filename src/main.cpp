#include "ProjectUtils.h"
#include <string>
#include <limits>
#include <iostream>

/*
Change Log:
--------------------------------------------------------------------------------
Change By: Blake McGahee
Change Date: 2025-06-28
Comment: Initial implementation of the command-line user interface and main application logic.
    - Setup of the main menu loop with options for data loading, generation, searching, and exit.
    - Integration of necessary standard library headers.
    - Basic structure to call `ProjectUtils` functions based on user choices.
    - Added display for menu, prompts, and output sections.
    - Implemented the option to load a dataset from a file using `ProjectUtils::loadAndSortDatasetFromFile`.
    - Created python scripts for genearting test data files. 
    - Created test data files to output into data directory

--------------------------------------------------------------------------------
Change By: Blake McGahee
Change Date: 2025-07-02
Comment: Added `findClosestValues` helper function and integrated enhanced search feedback.
    - `findClosestValues` function: A new utility to efficiently find and return up to 10 values closest to a target in a sorted dataset when the target is not found. This provides helpful context to the user.
        - Leverages `std::lower_bound` for efficient initial positioning and expands outwards.
        - Includes logic to handle boundary conditions and small datasets.
        - Sorts results by absolute difference to the target, then by value for tie-breaking.
    - Integrated the display of these closest values into the search results when a target is not found, improving user experience and troubleshooting insight.

--------------------------------------------------------------------------------
Change By: Blake McGahee
Change Date: 2025-07-04
Comment: Finalized search execution and result display.
    - Implemented calls to `ProjectUtils::measureSearchTime` for both Jump Search and the placeholder Interpolation Search to time their execution.
    - Ensured search results (found index or 'not found' status) and measured times (in milliseconds) are clearly displayed to the user.
    - Configured default parameters for random dataset generation for quick testing.

--------------------------------------------------------------------------------
Change By: Blake McGahee
Change Date: 2025-07-05
Comment: Refined team section comments for clarity and delegation since we were unable to meet on 7/5.
    - **Thiago's Section**: Streamlined instructions for the `interpolationSearch` implementation, providing the function signature and a clear directive for his task within the `ProjectUtils` namespace.
    - **Gerson's Section**: Streamlined instructions for the `main.cpp` for the user interface of Interpolation Search Implementation. 

--------------------------------------------------------------------------------
*/

// Helper function to find the 10 closest values to a target in a sorted dataset.
// This function is designed to be efficient by leveraging the sorted nature of the dataset.
// It finds the approximate insertion point of the target and then expands outwards
// to collect the nearest 10 values, handling boundary conditions gracefully.
std::vector<int> findClosestValues(const std::vector<int>& dataset, int target) {
    std::vector<int> closest_values; // Vector to store the results.
    if (dataset.empty()) {
        return closest_values; // Return empty if the dataset is empty.
    }

    // Find the iterator to the first element that is not less than 'target'.
    // This gives us the potential insertion point for 'target'.
    auto it = std::lower_bound(dataset.begin(), dataset.end(), target);

    // Determine the starting and ending indices for collecting closest values.
    // We want to collect up to 5 elements before 'it' and up to 5 elements at/after 'it'.
    int start_idx = 0;
    int end_idx = dataset.size() - 1;

    // Calculate a good starting point to collect 10 values around 'it'.
    // We aim for 'it' to be roughly in the middle of our 10-value window.
    int current_pos = std::distance(dataset.begin(), it);
    int window_start = std::max(0, current_pos - 5); // Start at most 5 elements before current_pos.
    int window_end = std::min((int)dataset.size() - 1, current_pos + 4); // End at most 4 elements after current_pos.

    // Adjust window if it goes out of bounds at the beginning or end.
    // If we can't get 10 elements from the right, try to get more from the left.
    if (window_end - window_start + 1 < 10) {
        window_start = std::max(0, (int)dataset.size() - 10);
    }
    // If we can't get 10 elements from the left, try to get more from the right.
    if (window_end - window_start + 1 < 10) {
        window_end = std::min((int)dataset.size() - 1, 9);
    }

    // Ensure the window size is at most 10, and within bounds.
    window_start = std::max(0, window_start);
    window_end = std::min((int)dataset.size() - 1, window_end);

    // Collect values within the determined window.
    for (int i = window_start; i <= window_end; ++i) {
        closest_values.push_back(dataset[i]);
        if (closest_values.size() >= 10) { // Stop if we have 10 values
            break;
        }
    }
    // If we have more than 10, trim to 10 (this can happen if the initial window calculation was too generous)
    if (closest_values.size() > 10) {
        closest_values.resize(10);
    }

    // Final check: if we have fewer than 10, and there are more elements, try to fill up to 10
    // This handles cases where the dataset itself is small or the target is at an extreme end.
    if (closest_values.size() < 10 && dataset.size() > closest_values.size()) {
        int needed = 10 - closest_values.size();
        for (int i = 0; i < needed && i < dataset.size(); ++i) {
            bool already_added = false;
            for (int val : closest_values) {
                if (val == dataset[i]) {
                    already_added = true;
                    break;
                }
            }
            if (!already_added) {
                closest_values.push_back(dataset[i]);
            }
        }
    }

    // Sort the collected closest values by their absolute difference to the target,
    // then by value for tie-breaking.
    std::sort(closest_values.begin(), closest_values.end(), [&](int a, int b) {
        long long diff_a = std::abs((long long)a - target);
        long long diff_b = std::abs((long long)b - target);
        if (diff_a == diff_b) {
            return a < b; // Tie-break by value
        }
        return diff_a < diff_b;
        });

    // Ensure we return at most 10 values.
    if (closest_values.size() > 10) {
        closest_values.resize(10);
    }

    return closest_values;
}




// --- GERSON'S SECTION: User Interface (CLI/Text) & Overall Project Integration ---
// Gerson, your task is to implement the main application logic and the command-line user interface.
// This will be done in a separate .cpp file (e.g., `main.cpp`) that includes this `ProjectUtils.h`.
//
// Your `main.cpp` should:
// 1. Include this `ProjectUtils.h` header, along with `<string>` and `<limits>` for robust input handling.
// 2. Implement a menu-driven program as outlined in the project proposal, offering options to:
//    - Load a dataset from a file (using `ProjectUtils::loadAndSortDatasetFromFile`).
//    - Generate a random dataset (using `ProjectUtils::generateAndSortDataset`).
//    - Perform Jump Search (using `ProjectUtils::jumpSearch` and `ProjectUtils::measureSearchTime`).
//    - Perform Interpolation Search (using `ProjectUtils::interpolationSearch` and `ProjectUtils::measureSearchTime`).
//    - Exit the program.
// 3. Handle user input for menu choices and search targets, including robust input validation (e.g., ensuring numeric input, handling non-numeric characters).
// 4. Display the results of searches (found/not found, index if found) and the measured timings for both search algorithms in a clear, formatted way.
// 5. Ensure the program gracefully handles cases where a search is attempted without a dataset loaded.


int main() {
    std::vector<int> dataset; // The dataset to be used for searching.
    // You might define default sizes/ranges for random generation here or prompt the user for them.

    int choice;
    do {
        // Display the main menu to the user.
        std::cout << "\n-----------------------------------------------\n";
        std::cout << "|          Search Algorithm Performance Study   |\n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "| 1. Load Dataset from File                     |\n"; // Option to load from a text file.
        std::cout << "| 2. Generate Random Dataset                    |\n"; // Option to generate a new random dataset.
        std::cout << "| 3. Search (Jump Search)                       |\n"; // Option to perform Jump Search.
        std::cout << "| 4. Search (Interpolation Search)              |\n"; // Option to perform Interpolation Search.
        std::cout << "| 5. Exit                                       |\n"; // Option to exit the program.
        std::cout << "-------------------------------------------------\n";
        std::cout << "Output:\n"; // Section for program output.
        std::cout << "> Enter choice: ";
        std::cin >> choice; // Read the user's menu choice.

        // Important: Clear the input buffer. This prevents issues when mixing `std::cin >> int`
        // with `std::getline` later, as `std::cin >> int` leaves the newline character in the buffer.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) { // Load Dataset from File
            // Prompt user for filename.
            // Call ProjectUtils::loadAndSortDatasetFromFile.
        } else if (choice == 2) { // User chose to generate a random dataset.
            // Define default parameters for random dataset generation.
            const int DEFAULT_GEN_SIZE = 1000000;
            const int DEFAULT_MIN_VAL = 1;
            const int DEFAULT_MAX_VAL = 10000000;
            ProjectUtils::generateAndSortDataset(dataset, DEFAULT_GEN_SIZE, DEFAULT_MIN_VAL, DEFAULT_MAX_VAL);
        } else if (choice == 3) { // User chose to perform Jump Search.
            // Check if a dataset is available before attempting to search.
            if (dataset.empty()) {
                std::cout << "No dataset loaded! Please load or generate a dataset first.\n";
                continue; // Go back to the main menu.
            }
            int target;
            std::cout << "> Enter value to search: ";
            // --- Input validation for target ---
            while (!(std::cin >> target)) { // Attempt to read integer. If fails...
                std::cout << "Invalid input. Please enter a valid integer: ";
                std::cin.clear(); // Clear the error flags on std::cin
                // Discard invalid input from the buffer until a newline is found
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear leftover newline

            int found_idx; // Variable to store the index if the target is found.
            // Call Blake's measureSearchTime to time the Jump Search.
            long long duration_us = ProjectUtils::measureSearchTime(
                [&](const std::vector<int>& arr, int val) { return ProjectUtils::jumpSearch(arr, val); },
                dataset, target, found_idx
            );
            // Display the search results.
            if (found_idx != -1) {
                std::cout << "Value " << target << " found at index " << found_idx << ".\n";
            }
            else {
                std::cout << "Value " << target << " not found.\n";
                std::vector<int> closest = findClosestValues(dataset, target);
                if (!closest.empty()) {
                    std::cout << "Closest values in the dataset:\n";
                    for (int val : closest) {
                        std::cout << val << " ";
                    }
                    std::cout << "\n";
                }
            }
            // Display the time taken, converted from microseconds to milliseconds.
            std::cout << "Jump Search Time: " << duration_us / 1000.0 << " ms\n";

        } else if (choice == 4) { // --- GERSON'S SECTION: Interpolation Search Implementation ---)
            // Check if dataset is loaded.
            // Prompt user for target value.
            // Call ProjectUtils::measureSearchTime with ProjectUtils::interpolationSearch (once Thiago implements it).
            // Display results (found/not found, index, time).
        else if (choice == 5) { // User chose to exit the program.
            std::cout << "Exiting program. Goodbye!\n";
        }
        else { // Invalid menu choice.
            std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    } while (choice != 5); // Continue the loop until the user chooses to exit (option 5).

    return 0; // Program ends successfully.
}
