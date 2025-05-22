import sys

def main():
    if len(sys.argv) < 3:
        print("No Arguments For Range Found")
    else:
        try:
            minRange = int(sys.argv[1])
            maxRange = int(sys.argv[2])
        except ValueError:
            print("Range values must be integers")
            return

        # Ensure minRange is less than maxRange
        if minRange >= maxRange:
            print("minRange must be less than maxRange")
            return

        lengths = []
        indexLengths = []

        # Calculate sequence lengths for each integer in the range
        for i in range(minRange, maxRange):
            j = calculateLen(i)
            if len(lengths) < 10:
                lengths.append(j)
                indexLengths.append(i)
            elif j > min(lengths):
                # Replace the smallest length and update the corresponding integer
                lengths[lengths.index(min(lengths))] = j
                indexLengths[lengths.index(min(lengths))] = i

        # Sorting the lengths and their corresponding integers together
        # Sort by sequence length in descending order
        sorted_lengths_and_indexes = sorted(zip(lengths, indexLengths), reverse=True, key=lambda x: x[0])

        # Unzip the sorted list back into lengths and indexLengths
        sorted_lengths, sorted_indexes = zip(*sorted_lengths_and_indexes)

        # Print sorted results
        print("Sorted based on sequence length:")
        for length, index in zip(sorted_lengths, sorted_indexes):
            print(f"{index} {length}")

        # Now sort based on the integer size (index) in descending order
        sorted_by_index = sorted(zip(lengths, indexLengths), reverse=True, key=lambda x: x[1])

        # Unzip the sorted list back into lengths and indexLengths
        sorted_lengths_by_index, sorted_indexes_by_index = zip(*sorted_by_index)

        print("\nSorted based on integer size:")
        for length, index in zip(sorted_lengths_by_index, sorted_indexes_by_index):
            print(f"{index} {length}")


def calculateLen(i):
    count = 0
    while i != 1:
        if i % 2 == 0:
            i = i // 2  # Use integer division
        else:
            i = i * 3 + 1
        count += 1
    return count

def findDuplicate(i, values):
    
if __name__ == "__main__":
    main()
