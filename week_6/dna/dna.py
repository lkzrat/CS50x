import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit('Usage: python dna.py data.csv sequence.txt')

    data_file = sys.argv[1]
    seq_file = sys.argv[2]

    # Read database file into a variable
    data = []

    with open(data_file) as file:
        reader = csv.DictReader(file)
        for row in reader:
            data.append(row)

    # Read DNA sequence file into a variable
    with open(seq_file) as file:
        reader = csv.reader(file)
        for row in reader:
            seq = row[0]

    # Find longest match of each STR in DNA sequence
    count = {}

    with open(data_file) as file:
        reader = csv.reader(file)
        for row in reader:
            row.remove('name')
            subseqs = row
            break

    for subseq in subseqs:
        count[subseq] = longest_match(seq, subseq)

    # Check database for matching profiles

    matcher = 'No match'

    check_dna = []
    check_count = []

    for subseq in subseqs:
        check_count.append(str(count[subseq]))

    for i in range(len(data)):
        for subseq in subseqs:
            check_dna.append(data[i][subseq])
        if check_dna == check_count:
            matcher = data[i]['name']
        check_dna = []

    print(matcher)

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
