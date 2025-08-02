#ifndef PROJECT_UTILS_H
#define PROJECT_UTILS_H

#include <vector>      // For std::vector to store the dataset.
#include <algorithm>   // For std::sort and std::min.
#include <random>      // For random number generation (std::mt19937, std::uniform_int_distribution).
#include <chrono>      // For timing algorithms (std::chrono::high_resolution_clock).
#include <iostream>    // For console input/output (e.g., printing status messages).
#include <cmath>       // For std::sqrt used in Jump Search.
#include <fstream>     // For file input/output operations (std::ifstream).
#include <string>      // For std::string and std::getline.
#include <unordered_set> // For ensuring uniqueness during data generation.


/*
Change Log:
--------------------------------------------------------------------------------
Change By: Blake McGahee
Change Date: 2025-06-28
Comment: Initial implementation of core utility functions for the "Efficient Data Retrieval: A Search Algorithm Performance Study" project. This includes:
    - `generateAndSortDataset`: Function to create large datasets of unique, sorted integers.
    - `jumpSearch`: Implementation of the Jump Search algorithm for sorted arrays.
    - `measureSearchTime`: A templated utility to accurately measure the execution time of search algorithms.
    - Initial setup of the `ProjectUtils` namespace and inclusion of necessary standard libraries (`<vector>`, `<algorithm>`, `<random>`, `<chrono>`, `<iostream>`, `<cmath>`).

--------------------------------------------------------------------------------
Change By: Blake McGahee
Change Date: 2025-07-01
Comment: Added robust data loading capabilities and ensured data integrity.
    - `loadAndSortDatasetFromFile`: New function introduced to load integer datasets from a specified file.
        - Includes comprehensive error handling for file opening, invalid data formats (`std::invalid_argument`, `std::out_of_range`).
        - Automatically **removes duplicate entries** from loaded data using `std::unique` after sorting, ensuring all datasets maintain uniqueness.
        - Sorts the loaded data using `std::sort`, which is a prerequisite for the search algorithms.

--------------------------------------------------------------------------------
Change By: Blake McGahee
Change Date: 2025-07-05
Comment: Refined team section comments for clarity and delegation since we were unable to meet on 7/5.
    - **Thiago's Section**: Streamlined instructions for the `interpolationSearch` implementation, providing the function signature and a clear directive for his task within the `ProjectUtils` namespace.
    - **Gerson's Section**: Streamlined instructions for the `main.cpp` for the user interface of Interpolation Search Implementation.
--------------------------------------------------------------------------------
Change By: Thiago Ramirez
Change Date: 2025-08-01
Comment: Completed and tested implementation of `interpolationSearch` within the `ProjectUtils` namespace.
    - Algorithm efficiently estimates target position based on data distribution, improving over binary search for uniformly distributed datasets.
    - Includes edge case handling for narrow ranges, single-element conditions, and potential integer overflows during probe calculation.

--------------------------------------------------------------------------------
*/


// This namespace encapsulates utility functions related to dataset management and search algorithms.
namespace ProjectUtils {

    /**
     * @brief Generates a large dataset of unique integers and sorts it.
     *
     * This function populates the provided vector with a specified number of unique random integers
     * within a defined range. After generation, the vector is sorted in ascending order.
     *
     * @param dataset A reference to the std::vector<int> to be populated and sorted.
     * @param num_elements The desired number of unique elements to generate.
     * @param min_val The minimum possible value for generated integers.
     * @param max_val The maximum possible value for generated integers.
     */
    void generateAndSortDataset(std::vector<int>& dataset, int num_elements, int min_val, int max_val) {
        dataset.clear(); // Clear any existing data in the vector.
        dataset.reserve(num_elements); // Pre-allocate memory for efficiency.

        // Initialize a Mersenne Twister random number generator with a time-based seed.
        std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        // Define a uniform integer distribution for the specified range.
        std::uniform_int_distribution<int> dist(min_val, max_val);

        std::unordered_set<int> unique_numbers; // Use a hash set to efficiently ensure uniqueness.
        while (unique_numbers.size() < num_elements) {
            unique_numbers.insert(dist(rng)); // Generate and insert unique numbers until target size is met.
        }
        // Assign the unique numbers from the set to the vector.
        dataset.assign(unique_numbers.begin(), unique_numbers.end());
        // Sort the dataset in ascending order, which is required for Jump Search and Interpolation Search.
        std::sort(dataset.begin(), dataset.end());

        std::cout << "Dataset generated and sorted with " << dataset.size() << " unique elements.\n";
    }

    /**
     * @brief Loads a dataset of integers from a specified file, removes duplicates, and sorts it.
     *
     * This function reads integers from the given file, with each integer expected on a new line.
     * It includes error handling for file opening and invalid data formats. After loading,
     * the dataset is sorted in ascending order, and then duplicate values are removed.
     *
     * @param dataset A reference to the std::vector<int> to be populated and sorted.
     * @param filename The path to the input file containing integers.
     * @return True if the file was successfully opened and data loaded, false otherwise.
     */
    bool loadAndSortDatasetFromFile(std::vector<int>& dataset, const std::string& filename) {
        dataset.clear(); // Clear any existing data in the vector.
        std::ifstream infile(filename); // Attempt to open the file for reading.

        if (!infile.is_open()) { // Check if the file failed to open.
            std::cerr << "Error: Could not open file '" << filename << "'. Please check the path and verify it is valid.\n";
            return false; // Indicate failure.
        }

        std::string line;
        int value;
        while (std::getline(infile, line)) { // Read the file line by line.
            try {
                value = std::stoi(line); // Convert the string line to an integer.
                dataset.push_back(value); // Add the integer to the dataset.
            }
            catch (const std::invalid_argument& e) { // Catch conversion errors (e.g., non-numeric data).
                std::cerr << "Warning: Invalid data in file '" << filename << "': '" << line << "' is not a valid integer. Skipping.\n";
            }
            catch (const std::out_of_range& e) { // Catch overflow/underflow errors for int type.
                std::cerr << "Warning: Number out of range in file '" << filename << "': '" << line << "'. Skipping.\n";
            }
        }
        infile.close(); // Close the file after reading.

        if (dataset.empty()) { // Check if any valid data was loaded.
            std::cerr << "Warning: No valid data loaded from file '" << filename << "'. Dataset is empty.\n";
            return false;
        }

        // Sort the loaded data in ascending order.
        std::sort(dataset.begin(), dataset.end());

        // --- NEW: Remove duplicates after sorting ---
        // std::unique moves all unique elements to the beginning of the range
        // and returns an iterator to the end of the unique range.
        auto last = std::unique(dataset.begin(), dataset.end());
        // erase then removes the elements from 'last' to the actual end of the vector.
        dataset.erase(last, dataset.end());
        // --- END NEW ---

        std::cout << "Dataset loaded, duplicates removed, and sorted from '" << filename << "' with " << dataset.size() << " elements.\n";
        return true; // Indicate success.
    }

    /**
     * @brief Implements the Jump Search algorithm for sorted arrays.
     *
     * Jump Search works by jumping ahead by fixed steps (block size) until the range
     * containing the target value is found. A linear search is then performed within that block.
     * The optimal block size is typically the square root of the array size.
     *
     * @param arr The sorted vector of integers to search within.
     * @param target The integer value to search for.
     * @return The index of the target if found, otherwise -1.
     */
    int jumpSearch(const std::vector<int>& arr, int target) {
        int n = arr.size();
        if (n == 0) return -1; // Handle empty array.

        // Determine the block size (square root of array size).
        int step = static_cast<int>(std::sqrt(n));

        // Find the block where the target might be present.
        int prev = 0; // Start of the current block.
        while (prev < n && arr[std::min(step, n) - 1] < target) {
            prev = step; // Move to the start of the next block.
            step += static_cast<int>(std::sqrt(n)); // Advance the 'step' marker.
            if (prev >= n) // If 'prev' has moved past the array end, target is not found.
                return -1;
        }

        // Perform linear search within the identified block (from 'prev' to 'step').
        while (prev < n && arr[prev] < target) {
            prev++; // Move linearly through the block.
        }

        // Check if the target is found at the current position.
        if (prev < n && arr[prev] == target) {
            return prev; // Target found, return its index.
        }

        return -1; // Target not found in the array.
    }


    /**
     * @brief Implements the Interpolation Search algorithm for sorted arrays.
     *
     * Interpolation Search is an improvement over Binary Search for uniformly
     * distributed data. It estimates the position of the target value based on
     * its value relative to the values at the ends of the search space.
     *
     * @param arr The sorted vector of integers to search within.
     * @param target The integer value to search for.
     * @return The index of the target if found, otherwise -1.
     */
    int interpolationSearch(const std::vector<int>& arr, int target) {
        int low = 0;
        int high = arr.size() - 1;

        while (low <= high && target >= arr[low] && target <= arr[high]) {
            // If the search space has shrunk to a single element.
            if (low == high) {
                if (arr[low] == target) return low;
                return -1; // Not found
            }

            // Calculate the probe position using the interpolation formula.
            // Using long long for intermediate calculations to prevent overflow,
            // especially when (high - low) * (target - arr[low]) is large.
            long long pos_calc = (long long)low + (((long long)high - low) / (arr[high] - arr[low])) * (target - arr[low]);

            // Ensure pos_calc is within valid array bounds [low, high].
            // This check is important to prevent out-of-bounds access if the formula
            // yields an invalid index due to non-uniform data or edge cases.
            if (pos_calc < low || pos_calc > high) {
                return -1; // Probe position is out of the current search range.
            }
            int pos = static_cast<int>(pos_calc);

            if (arr[pos] == target) {
                return pos; // Target found at probe position.
            }

            // Adjust search space based on comparison.
            if (arr[pos] < target) {
                low = pos + 1; // Target is in the right part.
            }
            else {
                high = pos - 1; // Target is in the left part.
            }
        }
        return -1; // Target not found.
    }


    /**
     * @brief Measures the execution time of a given search function.
     *
     * This templated function takes a search function (e.g., a lambda or function pointer),
     * the dataset, the target value, and a reference to store the found index.
     * It returns the duration of the search in microseconds.
     *
     * @tparam Func A callable type representing the search algorithm (e.g., `int(const std::vector<int>&, int)`).
     * @param search_func The search function to be measured.
     * @param dataset The dataset (vector) to search within.
     * @param target The value to search for.
     * @param result_index A reference to an int where the found index will be stored.
     * @return The duration of the search in microseconds.
     */
    template<typename Func>
    long long measureSearchTime(Func search_func, const std::vector<int>& dataset, int target, int& result_index) {
        auto start = std::chrono::high_resolution_clock::now(); // Record start time.
        result_index = search_func(dataset, target);             // Execute the search function.
        auto end = std::chrono::high_resolution_clock::now();   // Record end time.
        // Calculate and return the duration in microseconds.
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

} // namespace ProjectUtils

#endif // PROJECT_UTILS_H
