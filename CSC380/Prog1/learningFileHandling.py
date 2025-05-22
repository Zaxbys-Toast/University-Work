# Test program to help learn file handling in python
import os

f = open("testFile.txt", "rt")
print(f.read())
f.seek(0) # moves the pointer back to the start of the file

#Can use readline() to read a single line, can use a number in read(*) to read a certain number of lines
for line in f:
    print(line.strip())
