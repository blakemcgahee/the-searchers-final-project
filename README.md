Efficient Data Retrieval: A Search Algorithm Performance Study
Project Description
This project is a command-line application designed to study and compare the performance of two search algorithms for sorted integer datasets: Jump Search and Interpolation Search. The application provides a user-friendly interface to either load a dataset from a file or generate a large, random dataset. It then performs searches for a user-specified target value, accurately measuring and displaying the execution time for each algorithm.

A key feature of this tool is its ability to provide helpful context when a target value is not found by displaying a list of the closest values from the dataset, which can be useful for debugging and analysis.

Features
Algorithm Comparison: Directly compares the performance of Jump Search and Interpolation Search on the same dataset.

Flexible Data Handling:

Generate Dataset: Creates large, unique, and sorted random integer datasets with configurable size and range.

Load Dataset from File: Loads integer data from a text file, automatically sorting it and removing any duplicate entries to ensure data integrity.

Accurate Performance Measurement: Utilizes a high-resolution timer to measure search times in microseconds. To provide a stable and accurate measurement, the search is run multiple times (1000) and the average time is reported.

Enhanced User Feedback: When a search fails, the program displays a list of the 10 values from the dataset that are closest to the target value.

Menu-Driven Interface: A clean and simple command-line menu guides the user through all available options.

How to Compile and Run
This project consists of two main C++ source files: a header file (ProjectUtils.h) and the main application file (main.cpp).

Prerequisites:
You will need a C++ compiler such as g++ to compile the program.

Compilation:
Navigate to the directory containing the source files and use the following command to compile the application:

g++ main.cpp -o search_app

This command will create an executable file named search_app.

Execution:
Run the compiled program from your terminal:

./search_app

Usage
Once the program is running, you will be presented with a menu of options:

Load Dataset from File: Prompts you to enter the path to a text file containing integers (one per line). The application will list several available sample files in the data/ directory.

Generate Random Dataset: Generates a new, large dataset of 1,000,000 unique, sorted integers.

Search (Jump Search): Performs a Jump Search on the currently loaded dataset for a value you specify.

Search (Interpolation Search): Performs an Interpolation Search on the currently loaded dataset for a value you specify.

Exit: Closes the program.

The program will display the search results and the average time taken for the operation in the "Output" section.

File Structure
ProjectUtils.h: Contains the core utility functions, including the implementations for jumpSearch, interpolationSearch, dataset generation, and performance timing.

main.cpp: Implements the command-line user interface, handles user input, and orchestrates calls to the functions in ProjectUtils.

Team & Contributions
This project was a collaborative effort with the following key contributions:

Blake McGahee: Initial project setup, core utility functions (generateAndSortDataset, loadAndSortDatasetFromFile, jumpSearch, measureSearchTime), and the findClosestValues helper function. He also finalized the search execution logic, enhanced timing measurements, and refactored the menu handling.

Thiago Ramirez: Implemented and tested the interpolationSearch algorithm.

Gerson Diaz: Developed and updated the command-line user interface in main.cpp to integrate all project functions and provide a smooth user experience.
