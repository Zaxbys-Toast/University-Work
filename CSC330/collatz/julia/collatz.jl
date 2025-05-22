function main(args)
    if length(args) < 2
        println("No Arguments For Range Found")
        return
    end

    # Declare min_range and max_range at the start
    min_range = 0
    max_range = 0

    try
        min_range = parse(Int, args[1])
        max_range = parse(Int, args[2])
    catch e
        println("Range values must be integers")
        return
    end

    # Ensure min_range is less than max_range
    if min_range >= max_range
        println("minRange must be less than maxRange")
        return
    end

    lengths = Int[]
    index_lengths = Int[]

    # Calculate sequence lengths for each integer in the range
    for i in min_range:max_range - 1
        j = calculate_len(i)
        if length(lengths) < 10
            push!(lengths, j)
            push!(index_lengths, i)
        elseif j > minimum(lengths)
            min_index = argmin(lengths)
            lengths[min_index] = j
            index_lengths[min_index] = i
        end
    end

    # Sort lengths and indexes by sequence length in descending order
    sorted_lengths_and_indexes = sort(collect(zip(lengths, index_lengths)), by=x->x[1], rev=true)

    # Print sorted results by sequence length
    println("Sorted based on sequence length:")
    for (length, index) in sorted_lengths_and_indexes
        println("$index $length")
    end

    # Sort by the integer value (index) in descending order
    sorted_by_index = sort(collect(zip(lengths, index_lengths)), by=x->x[2], rev=true)

    println("\nSorted based on integer size:")
    for (length, index) in sorted_by_index
        println("$index $length")
    end
end

# Define a function to calculate the sequence length
function calculate_len(i::BigInt)
    count = 0
    while i != 1
        if i % 2 == 0
            i ÷= 2  # Integer division
        else
            i = i * 3 + 1
        end
        count += 1
    end
    return count
end

# Entry point
if abspath(PROGRAM_FILE) == @__FILE__
    main(ARGS)
end
