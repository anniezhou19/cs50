import csv
from sys import argv

# Check if input is valid, if not, print error message.
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")

# Read the DNA sequence from the file
# Store the information in a string
with open(argv[2]) as s_file:
    String = s_file.read()

# Create a dictionary to store the DNA sequences that are to be counted
sequence = {}
# Extract the sequences from the database into a list
with open(argv[1], "r") as file:
    data = csv.reader(file)
    sequence_list = next(data)
    sequence_list.pop(0)

# Copy the list into a dictionary where the genes are the keys
for item in sequence_list:
    sequence[item] = 1

# Iterate through the DNA sequence
# Add a counter — if repetitions of the values from sequence dictionaries are found, add them up
for key in sequence:
    l = len(key)
    temp = 0
    max_count = 0
    for i in range(len(String)):
        while temp > 1:
            temp -= 1
            continue
        if String[i:i+l] == key:
            while String[i-l:i] == String[i:i+l]:
                temp += 1
                i += l
            if temp > max_count:
                max_count += temp
    sequence[key] += max_count

# Open the database file
# Iterate through and compare to the sequences dictionary
# If there is a match, print the name of the person; if not, no match.
with open(argv[1]) as file:
    data = csv.DictReader(file)
    for row in data:
        match = 0
        for key in sequence:
            if sequence[key] == int(row[key]):
                match += 1
        if match == len(sequence):
            print(row['name'])
            exit()
    print("No match")
