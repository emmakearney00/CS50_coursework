import csv
from sys import argv

def main():

    # Check for command-line usage
    if len(argv) != 3:
        print("Usage: python dna.py file1.csv file2.txt")
        exit(1)
    # Read database file into a variable
    else:
        file1 = open(argv[1], "r")
        dbase = csv.DictReader(file1)
        str_list = dbase.fieldnames[1:]

    # Read DNA sequence file into a variable
        file2 = open(argv[2], "r")
        sequence = file2.read()

    # Find longest match of each STR in DNA sequence
        n = len(str_list)
        sequences = {}
        for i in range(n):
            max = longest_match(sequence, str_list[i])
            sequences[str_list[i]] = max


    # Check database for matching profiles
        for row in dbase:
            match = 0
            for str_list[i] in sequences:
                if sample[str] == row[str]:
                    match = match + 1
            if match == len(str_list):
                print(row['name'])
            else:
                print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

#python dna.py databases/small.csv sequences/1.txt