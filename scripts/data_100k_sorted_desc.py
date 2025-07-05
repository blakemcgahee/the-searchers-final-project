import random

# This script generates 100,000 unique integers, sorted in descending order,
# and saves them to 'data/data_100k_sorted_desc.txt'.

num_elements = 100000
min_val = 1
max_val = 1000000 # This range is used for random generation, but for sorted_desc, we just generate 100000 down to 1

# This tells the script to go up one directory from 'scripts/'
# and then look for the 'data/' folder.
# For data_100k_sorted_desc.txt, we simply generate numbers from num_elements down to 1
# and write them directly, as they are already unique and in order.
with open("../data/data_100k_sorted_desc.txt", "w") as f:
    for i in range(100000, 0, -1): # Generates numbers from 100,000 down to 1
        f.write(str(i) + "\n")
