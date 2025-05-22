import heapq
import sys

def findLength(i):
    if i == 1:
        return 1
    elif i % 2 == 0:
        return 1 + findLength(i // 2)
    else:
        return 1 + findLength(i * 3 + 1)

class collatzValue:
    def __init__(self, value, length):
        self.value = value
        self.length = length

    def __lt__(self, other):
        return(self.length, -self.value) < (other.length, -other.value)

    def __repr__(self):
        return f"({self.value}, {self.length})"

def computeInRange(start, end):
    min_heap = []
    
    for i in range(start, end):
        length = findLength(i)
        c_value = collatzValue(i, length)

        if len(min_heap) < 10:
            if not any(v.length == c_value.length for v in min_heap):
                heapq.heappush(min_heap, c_value)

        else:
            if not any(v.length == c_value.length for v in min_heap):
                if c_value > min_heap[0]:
                    heapq.heappushpop(min_heap, c_value)

    sorted_by_length = sorted(min_heap, key=lambda x: (-x.length, x.value))
    sorted_by_value = sorted(min_heap, key=lambda x: x.value)
    return sorted_by_length, sorted_by_value

def main():
    if len(sys.argv) < 3:
        print("Must enter an integer range")
        return

    try:
        start = int(sys.argv[1])
        end = int(sys.argv[2])

        if start < 1 or end < 1:
            print("Input values must be between 1 and 2.1 billion.")
            return

        if start > end:
            start, end = end, start

        sorted_by_length, sorted_by_value = computeInRange(start, end)

        print("Sorted based on sequence length:")
        for collatz_value in sorted_by_length:
            print(f"{collatz_value.value} {collatz_value.length}")

        print("\nSorted based on integer size:")
        for collatz_value in sorted_by_value:
            print(f"{collatz_value.value} {collatz_value.length}")

    except ValueError:
        print("Both inputs must be integers.")

if __name__ == "__main__":
    main()
