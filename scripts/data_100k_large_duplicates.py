import random

num_elements = 100000
min_val = 1
max_val = 1000 # A small range to ensure many duplicates

# This tells the script to go up one directory from 'scripts/'
# and then look for the 'data/' folder.
with open("../data/data_large_duplicates.txt", "w") as f:
    for _ in range(num_elements):
        f.write(str(random.randint(min_val, max_val)) + "\n")
