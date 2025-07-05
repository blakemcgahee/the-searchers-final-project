import random

num_elements = 100000
min_val = 1
max_val = 100000000 # Much larger range

unique_numbers = set()
while len(unique_numbers) < num_elements:
    unique_numbers.add(random.randint(min_val, max_val))

# This tells the script to go up one directory from 'scripts/'
# and then look for the 'data/' folder.
with open("../data/data_100k_sparse.txt", "w") as f:
    for num in unique_numbers:
        f.write(str(num) + "\n")
