using System;
using System.Collections.Generic;
using System.Linq;

public struct CollatzValue
{
    public int Value;
    public int CLength;

    public CollatzValue(int value, int cLength)
    {
        Value = value;
        CLength = cLength;
    }

    public override string ToString()
    {
        return $"{Value}   {CLength}";
    }
}

public class CollatzCalculator
{
    public static int GetLength(int i)
    {
	if( i == 1 ){
	    return 1;
	}
	else if( i % 2 == 0) {
	    return 1 + GetLength(i / 2);
	} 
	else {
	    return 1 + GetLength(i * 3 + 1);
	}
    }

    public static (List<CollatzValue> SortedByLength, List<CollatzValue> SortedByValue) ComputeCollatzInRange(int start, int stop)
    {
        List<CollatzValue> top10 = new List<CollatzValue>();

        Func<CollatzValue, CollatzValue, bool> Lt = (a, b) =>
            (a.CLength < b.CLength) || (a.CLength == b.CLength && a.Value > b.Value);

        for (int i = start; i <= stop; i++)
        {
            int collatzLength = GetLength(i);
            int val = i;

            int existingIndex = top10.FindIndex(x => x.CLength == collatzLength);
            if (existingIndex != -1)
            {
                CollatzValue existing = top10[existingIndex];
                if (val < existing.Value)
                {
                    top10.RemoveAt(existingIndex);
                    top10.Add(new CollatzValue(val, collatzLength));
                    top10.Sort((a, b) => Lt(a, b) ? -1 : 1);
                }
            }
            else
            {
                if (top10.Count < 10)
                {
                    top10.Add(new CollatzValue(val, collatzLength));
                    top10.Sort((a, b) => Lt(a, b) ? -1 : 1);
                }
                else
                {
                    CollatzValue smallest = top10[0];
                    CollatzValue newItem = new CollatzValue(val, collatzLength);
                    if (Lt(smallest, newItem))
                    {
                        top10.RemoveAt(0);
                        top10.Add(newItem);
                        top10.Sort((a, b) => Lt(a, b) ? -1 : 1);
                    }
                }
            }
        }

        var sortedByLength = top10.OrderByDescending(x => x.CLength).ThenBy(x => x.Value).ToList();
        var sortedByValue = top10.OrderBy(x => x.Value).ToList();

        return (sortedByLength, sortedByValue);
    }

    public static void Main(string[] args)
    {
        if (args.Length < 2)
        {
            Console.WriteLine("Usage: CollatzCalculator <start> <end>");
            Environment.Exit(1);
        }

        int start = int.Parse(args[0]);
        int stop = int.Parse(args[1]);

        var (sortedByLength, sortedByValue) = ComputeCollatzInRange(start, stop);

        Console.WriteLine("Sorted by length:");
        foreach (var cv in sortedByLength)
        {
            Console.WriteLine(cv);
        }

        Console.WriteLine("Sorted by value:");
        foreach (var cv in sortedByValue)
        {
            Console.WriteLine(cv);
        }
    }
}

