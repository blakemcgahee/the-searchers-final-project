import random

num_elements = 100000
min_val = -500000
max_val = 500000

# Loop until the desired number of unique elements is reached.
unique_numbers = set()
# Generate a random integer within the specified range [min_val, max_val]
# and add it to the 'unique_numbers' set. If the number already exists,
while len(unique_numbers) < num_elements:
    unique_numbers.add(random.randint(min_val, max_val))
    
# This tells the script to go up one directory from 'scripts/'
# and then look for the 'data/' folder.
with open("../data/data_negative_numbers.txt", "w") as f:
    for num in unique_numbers:
        f.write(str(num) + "\n")
