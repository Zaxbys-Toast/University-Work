function calculate_len(i::Int)
    if i == 1
        return 0
    elseif i % 2 == 0
        return 1 + calculate_len(i ÷ 2)  # Division for even numbers
    else
        return 1 + calculate_len(i * 3 + 1)  # Multiply by 3 and add 1 for odd numbers
    end
end

function main()
    # Get command-line arguments
    args = ARGS
    if length(args) < 2
        println("No Arguments For Range Found")
        return
    end
    
    min_range = 0
    max_range = 0
    # Parse command-line arguments
    try
        min_range = parse(Int, args[1])
        max_range = parse(Int, args[2])
    catch
        println("Range values must be integers")
        return
    end

    if min_range >= max_range
        println("minRange must be less than maxRange")
        return
    end

    lengths = Int[]
    index_lengths = Int[]

    # Calculate sequence lengths for each integer in the range
    for i in min_range:max_range-1
        sequence_length = calculate_len(i)
        if length(lengths) < 10
            push!(lengths, sequence_length)
            push!(index_lengths, i)
        elseif sequence_length > minimum(lengths)
            min_index = argmin(lengths)
            lengths[min_index] = sequence_length
            index_lengths[min_index] = i
        end
    end

    # Sort by sequence length in descending order
    sorted_by_length = sort(collect(zip(lengths, index_lengths)), by = x -> x[1], rev = true)

    println("Sorted based on sequence length:")
    for (length, index) in sorted_by_length
        println("$index $length")
    end

    # Sort by integer size (index) in descending order
    sorted_by_index = sort(collect(zip(lengths, index_lengths)), by = x -> x[2], rev = true)

    println("\nSorted based on integer size:")
    for (length, index) in sorted_by_index
        println("$index $length")
    end
end

# Call the main function
main()
