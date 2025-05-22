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

        if minRange >= maxRange:
            print("minRange must be less than maxRange")
            return

        lengths = []
        indexLengths = []

        for i in range(minRange, maxRange):
            length = 0
            j = findLength(i, length)
            if len(lengths) < 10:
                lengths.append(j)
                indexLengths.append(i)
            elif j > min(lengths):
                lengths[lengths.index(min(lengths))] = j
                indexLengths[lengths.index(min(lengths))] = i
        sorted_lengths_and_indexes = sorted(zip(lengths, indexLengths), reverse=True, key=lambda x: x[0])

        sorted_lengths, sorted_indexes = zip(*sorted_lengths_and_indexes)

        print("Sorted based on sequence length:")
        for length, index in zip(sorted_lengths, sorted_indexes):
            print(f"{index} {length}")

        sorted_by_index = sorted(zip(lengths, indexLengths), reverse=True, key=lambda x: x[1])

        sorted_lengths_by_index, sorted_indexes_by_index = zip(*sorted_by_index)

        print("\nSorted based on integer size:")
        for length, index in zip(sorted_lengths_by_index, sorted_indexes_by_index):
            print(f"{index} {length}")





def findLength(i, length):
    if i == 1:
        return length
    elif i % 2 == 0:
        return findLength(i/2, length + 1)
    else:
        return findLength((i * 3) + 1, length + 1)
main()
