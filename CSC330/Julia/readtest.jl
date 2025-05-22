#!/usr2/local/julia-1.10.4/bin/julia

function readtest()
    filename = "testhands"
    path = "/pub/pounds/CSC330/poker/"
    fullpath = joinpath(path, filename)  # Concatenate the path and filename

    # Open the file, read the line, and print it
    open(fullpath, "r") do file
        lineOfText = readline(file)
        println(lineOfText)
    end
end

readtest()

