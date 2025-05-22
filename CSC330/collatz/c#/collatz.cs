using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main(string[] args)
    {
        if (args.Length < 2)
        {
            Console.WriteLine("No Arguments For Range Found");
            return;
        }

        int minRange, maxRange;

        // Parse command-line arguments
        if (!int.TryParse(args[0], out minRange) || !int.TryParse(args[1], out maxRange))
        {
            Console.WriteLine("Range values must be integers");
            return;
        }

        if (minRange >= maxRange)
        {
            Console.WriteLine("minRange must be less than maxRange");
            return;
        }

        var lengths = new List<int>();
        var indexLengths = new List<int>();

        // Calculate sequence lengths for each integer in the range
        for (int i = minRange; i < maxRange; i++)
        {
            int sequenceLength = CalculateLen(i);
            if (lengths.Count < 10)
            {
                lengths.Add(sequenceLength);
                indexLengths.Add(i);
            }
            else if (sequenceLength > lengths.Min())
            {
                int minIndex = lengths.IndexOf(lengths.Min());
                lengths[minIndex] = sequenceLength;
                indexLengths[minIndex] = i;
            }
        }

        // Sort by sequence length in descending order
        var sortedByLength = lengths
            .Zip(indexLengths, (length, index) => new { Length = length, Index = index })
            .OrderByDescending(x => x.Length)
            .ToList();

        Console.WriteLine("Sorted based on sequence length:");
        foreach (var item in sortedByLength)
        {
            Console.WriteLine($"{item.Index} {item.Length}");
        }

        // Sort by integer size (index) in descending order
        var sortedByIndex = lengths
            .Zip(indexLengths, (length, index) => new { Length = length, Index = index })
            .OrderByDescending(x => x.Index)
            .ToList();

        Console.WriteLine("\nSorted based on integer size:");
        foreach (var item in sortedByIndex)
        {
            Console.WriteLine($"{item.Index} {item.Length}");
        }
    }

    static int CalculateLen(int i)
    {
        int count = 0;
        while (i != 1)
        {
            if (i % 2 == 0)
                i /= 2;
            else
                i = i * 3 + 1;
            count++;
        }
        return count;
    }
}
