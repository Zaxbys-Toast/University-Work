# The game of life...

import sys
import numpy as np
import random
def main():
	# Need to do some of -f flag check, and then need something to open and read the file
	# This step will also include checking that the command line input is what was expected
	# The method for opening files can check if the files were opened properly
	print("Artificial Life Simulation of Game of Life")
	print("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^")
	print("Each cell with one or no neighbors dies, as if by loneliness.")
	print("Each cell with four or more neighbors dies, as if by overpopulation.")
	print("Each cell with two or three neighbors survives.")
	print("Each cell with three neighbors becomes overpopulated.")
	print("Each cell that ages over 10 generations dies.\n")

	numGens = 0
	numGens = int(input("How many generations would you like to simulate? "))
	
	colony = np.zeros((20,20))
	colony = openBoard(colony)
	printColony(colony)
	for i in range(numGens):
		colony = applyRules(colony)
		print("Colony after ", i+1, " generations")
		printColony(colony)	

# Reads a file to creaate the colony or creates a  random colony
def openBoard(colony): 
	# Opens a file from the command line input
	if len(sys.argv) > 1 and sys.argv[1] == "-f":
		try:
			filename = sys.argv[2]
		
			with open(filename, 'r') as file:
				for i, line in enumerate(file):
					for j, char in enumerate(line.strip().split()):
						if char == 'X':
							colony[i][j] = 1
		except FileNotFoundError:
			print("Error, file not found")
			sys.exit(1)
	else:	
		for i in range(20):
			for j in range(20):
				colony[i][j] = random.randint(0,1)
	return colony
	
def printColony(colony):
	for row in colony:
		for cell in row:
				print("\033[31mX\033[0m" if cell == 1 else "0", end=" ") # the weird characters here are to print the
								   			 # x's in red so they're easier to see
		print()

# Count neighbors of a specific coordinate, used to determine the survival and growth of a cell
def countNeighbors(colony, i, j):
	count = 0
	for x in range(max(0, i-2), min(len(colony[0]), i+2)):
		for y in range(max(0, j-2), min(len(colony[0]), j+2)):
			if (x, y) != (i, j) and colony[x][y] > 0:
				count += 1
	return count

# Applies the rules seen in the text of the main function
def applyRules(colony):
	newColony = np.zeros_like(colony)
	
	for i in range(len(colony)):
		for j in range(len(colony[0])):
			neighbors = countNeighbors(colony, i, j)
			if colony[i][j] == 0:
				if neighbors <= 1:
					newColony[i][j] = 0
				elif neighbors == 3:
					newColony[i][j] = 1
			if colony[i][j] < 10:
				if neighbors == 2 or neighbors == 3:
					newColony[i][j] = colony[i][j] + 1
			else:
				newColony[i][j] = 0
	return newColony

# Calling the main function
if __name__ == "__main__":
	main()

