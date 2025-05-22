struct CollatzValue
    value::BigInt
    c_length::BigInt
end

function Base.show(io::IO, cv::CollatzValue)
    print(io, cv.value, "   ", cv.c_length)
end

function get_length(i::BigInt)
    if i == 1
	return 1
    elseif i % 2 == 0
	return 1 + get_length(div(i, 2))
    else
	return 1 + get_length(i * 3 + 1)
    end
end

function computeCollatzInRange(start::Int, stop::Int)
    top_10 = Vector{CollatzValue}()

    lt(a::CollatzValue, b::CollatzValue) = (a.c_length < b.c_length) || (a.c_length == b.c_length && a.value > b.value)

    start_int = Int(start)
    stop_int = Int(stop)

    for i in start_int:stop_int
        collatz_length = get_length(BigInt(i))
        val = BigInt(i)

        existing_index = findfirst(x -> x.c_length == collatz_length, top_10)
        if existing_index !== nothing
            existing = top_10[existing_index]
            if val < existing.value
                deleteat!(top_10, existing_index)
                push!(top_10, CollatzValue(val, collatz_length))
                sort!(top_10, lt=lt)
            end
        else
            if length(top_10) < 10
                push!(top_10, CollatzValue(val, collatz_length))
                sort!(top_10, lt=lt)
            else
                smallest = top_10[1]
                new_item = CollatzValue(val, collatz_length)
                if lt(smallest, new_item)
                    popfirst!(top_10)
                    push!(top_10, new_item)
                    sort!(top_10, lt=lt)
                end
            end
        end
    end

    sorted_by_length = sort(top_10, by = x -> (-x.c_length, x.value))
    sorted_by_value = sort(top_10, by = x -> x.value)

    return sorted_by_length, sorted_by_value
end

if length(ARGS) < 2
    println("Usage: julia fixed.jl <start> <end>")
    exit(1)
end

start = parse(Int, ARGS[1])
stop = parse(Int, ARGS[2])

sorted_by_length, sorted_by_value = computeCollatzInRange(start, stop)

println("Sorted by length:")
for cv in sorted_by_length
    println(cv)
end

println("Sorted by value:")
for cv in sorted_by_value
    println(cv)
end
