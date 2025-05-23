# Define the C# compiler and project name
CSC = csc
PROJECT_NAME = PokerGame

# List of source files
SOURCES = card.cs deck.cs player.cs poker.cs

# Target to build the project
all: $(PROJECT_NAME).exe

# Compile the C# source files
$(PROJECT_NAME).exe: $(SOURCES)
	$(CSC) $(SOURCES) -out:$(PROJECT_NAME).exe

# Target to run the project
run: $(PROJECT_NAME).exe
	mono $(PROJECT_NAME).exe

# Clean up generated files
clean:
	rm -f $(PROJECT_NAME).exe

.PHONY: all run clean

