#ifndef PROJECT_UTILS_H
#define PROJECT_UTILS_H

#include <vector>     // For std::vector to store our dataset
#include <algorithm>  // For std::sort and std::min
#include <random>     // For random number generation (std::mt19937, std::uniform_int_distribution)
#include <chrono>     // For timing algorithms (std::chrono::high_resolution_clock)
#include <iostream>   // For basic input/output (e.g., in main for testing)
#include <cmath>      // For std::sqrt in Jump Search
#include <fstream>    // NEW: For file input/output operations (std::ifstream)
#include <string>     // NEW: For std::getline and string operations
#include <unordered_set> // For ensuring uniqueness in data generation

// --- BLAKE'S SECTION: Data Generation & Sorting, Jump Search Implementation, Performance Analysis Setup ---

namespace ProjectUtils {

    /**
     * @brief Generates a large dataset of unique integers and sorts it.
     *
     * This function populates the given vector with a specified number of unique random integers
     * within a defined range, and then sorts the vector in ascending order.
     *
     * @param dataset A reference to the std::vector<int> to be populated and sorted.
     * @param num_elements The desired number of unique elements (e.g., 1,000,000).
     * @param min_val The minimum possible value for generated integers.
     * @param max_val The maximum possible value for generated integers.
     */
    void generateAndSortDataset(std::vector<int>& dataset, int num_elements, int min_val, int max_val) {
        dataset.clear();
        dataset.reserve(num_elements);

        std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(min_val, max_val);

        std::unordered_set<int> unique_numbers;
        while (unique_numbers.size() < num_elements) {
            unique_numbers.insert(dist(rng));
        }
        dataset.assign(unique_numbers.begin(), unique_numbers.end());
        std::sort(dataset.begin(), dataset.end());

        std::cout << "Dataset generated and sorted with " << dataset.size() << " unique elements." << std::endl;
    }

    /**
     * @brief Loads a dataset of integers from a specified file and sorts it.
     *
     * This is a NEW function for Blake's responsibility, allowing data to be sourced from a file.
     * Each integer is expected to be on a new line in the file.
     *
     * @param dataset A reference to the std::vector<int> to be populated and sorted.
     * @param filename The path to the input file containing integers.
     * @return True if the file was successfully opened and data loaded, false otherwise.
     */
    bool loadAndSortDatasetFromFile(std::vector<int>& dataset, const std::string& filename) {
        dataset.clear(); // Clear any existing data
        std::ifstream infile(filename); // Open the file for reading

        if (!infile.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return false; // Return false if file opening failed
        }

        std::string line;
        int value;
        while (std::getline(infile, line)) { // Read file line by line
            try {
                value = std::stoi(line); // Convert string line to integer
                dataset.push_back(value); // Add to dataset
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Warning: Invalid data in file '" << filename << "': '" << line << "' is not an integer. Skipping." << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cerr << "Warning: Number out of range in file '" << filename << "': '" << line << "'. Skipping." << std::endl;
            }
        }
        infile.close(); // Close the file

        if (dataset.empty()) {
            std::cerr << "Warning: No valid data loaded from file " << filename << ". Dataset is empty." << std::endl;
            return false;
        }

        std::sort(dataset.begin(), dataset.end()); // Sort the loaded data
        std::cout << "Dataset loaded and sorted from '" << filename << "' with " << dataset.size() << " elements." << std::endl;
        return true; // Return true on successful load
    }


    /**
     * @brief Implements the Jump Search algorithm.
     *
     * @param arr The sorted vector of integers to search within.
     * @param target The integer value to search for.
     * @return The index of the target if found, otherwise -1.
     */
    int jumpSearch(const std::vector<int>& arr, int target) {
        int n = arr.size();
        if (n == 0) return -1;

        int step = static_cast<int>(std::sqrt(n));

        int prev = 0;
        while (prev < n && arr[std::min(step, n) - 1] < target) {
            prev = step;
            step += static_cast<int>(std::sqrt(n));
            if (prev >= n)
                return -1;
        }

        while (prev < n && arr[prev] < target) {
            prev++;
        }

        if (prev < n && arr[prev] == target) {
            return prev;
        }

        return -1;
    }

    /**
     * @brief Measures the execution time of a given search function.
     *
     * @tparam Func A callable type (e.g., a lambda or function pointer) representing the search algorithm.
     * @param search_func The search function to measure.
     * @param dataset The dataset to search within.
     * @param target The value to search for.
     * @param result_index A reference to an int where the found index will be stored.
     * @return The duration of the search in microseconds.
     */
    template<typename Func>
    long long measureSearchTime(Func search_func, const std::vector<int>& dataset, int target, int& result_index) {
        auto start = std::chrono::high_resolution_clock::now();
        result_index = search_func(dataset, target);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

} // namespace ProjectUtils

// --- THIAGO'S SECTION: Interpolation Search Implementation, Search Query Logic, Result Verification ---
// Thiago, your Interpolation Search function will go here.
// It should have a signature similar to:
// int interpolationSearch(const std::vector<int>& arr, int target);
// You will also handle the logic for taking user input for search queries
// and verifying/displaying the results using the `measureSearchTime` helper.
//
// Example placeholder for Thiago's function:
/*
namespace ProjectUtils {
    int interpolationSearch(const std::vector<int>& arr, int target) {
        // Thiago's interpolation search implementation here
        // ...
        return -1; // Return index if found, -1 otherwise
    }
} // namespace ProjectUtils
*/


// --- GERSON'S SECTION: User Interface (CLI/Text) & Output Formatting, Overall Project Integration ---
// Gerson, your main application logic and UI will go here, likely in a separate .cpp file
// (e.g., `main.cpp`) that includes this `ProjectUtils.h`.
// You will implement the menu-driven program and call the functions from ProjectUtils.
//
// Example structure for Gerson's `main.cpp`:
/*
#include "ProjectUtils.h" // Include this header

int main() {
    std::vector<int> dataset;
    const int DATASET_SIZE = 1000000;
    const int MIN_VAL = 1;
    const int MAX_VAL = 10000000;

    // Call Blake's data generation function
    ProjectUtils::generateAndSortDataset(dataset, DATASET_SIZE, MIN_VAL, MAX_VAL);

    // Gerson's UI loop
    int choice;
    do {
        // Print menu options
        std::cout << "\n-------------------------------------------------\n";
        std::cout << "|           Search Algorithm Performance Study           |\n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "| 1. Generate Dataset                             |\n";
        std::cout << "| 2. Search (Jump Search)                         |\n";
        std::cout << "| 3. Search (Interpolation Search)                |\n";
        std::cout << "| 4. Exit                                         |\n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "Output:\n";
        std::cout << "> Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            // Re-generate dataset
            ProjectUtils::generateAndSortDataset(dataset, DATASET_SIZE, MIN_VAL, MAX_VAL);
        } else if (choice == 2) {
            // Call Blake's Jump Search and measure time
            int target;
            std::cout << "> Enter value to search: ";
            std::cin >> target;
            int found_idx;
            long long duration_us = ProjectUtils::measureSearchTime(
                [&](const std::vector<int>& arr, int val){ return ProjectUtils::jumpSearch(arr, val); },
                dataset, target, found_idx
            );
            if (found_idx != -1) {
                std::cout << "Value " << target << " found at index " << found_idx << ".\n";
            } else {
                std::cout << "Value " << target << " not found.\n";
            }
            std::cout << "Jump Search Time: " << duration_us / 1000.0 << " ms\n";

        } else if (choice == 3) {
            // Call Thiago's Interpolation Search and measure time
            // Thiago will implement this part of the UI interaction and call his function.
            // Example:
            // int target;
            // std::cout << "> Enter value to search: ";
            // std::cin >> target;
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

        } else if (choice == 4) {
            std::cout << "Exiting program. Goodbye!\n";
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
*/

#endif // PROJECT_UTILS_H
