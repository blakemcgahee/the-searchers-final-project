import random

# This script generates 100,000 unique integers, sorted in ascending order,
# and saves them to 'data/data_100k_sorted_asc.txt'.

num_elements = 100000
min_val = 1
max_val = 1000000 # This range is used for random generation, but for sorted_asc, we just generate 1 to 100000

# This tells the script to go up one directory from 'scripts/'
# and then look for the 'data/' folder.
# For data_100k_sorted_asc.txt, we simply generate numbers from 1 to num_elements
# and write them directly, as they are already unique and in order.
with open("../data/data_100k_sorted_asc.txt", "w") as f:
    for i in range(1, 100001): # Generates numbers from 1 to 100,000
        f.write(str(i) + "\n")