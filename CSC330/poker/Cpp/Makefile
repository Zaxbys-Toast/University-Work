all: main

main: main.o deck.o player.o card.o
	g++ -Wall -g main.o deck.o player.o card.o -o main

main.o: main.cpp
	g++ -Wall -g -c main.cpp

deck.o: deck.cpp
	g++ -Wall -g -c deck.cpp

player.o: player.cpp
	g++ -Wall -g -c player.cpp

card.o: card.cpp
	g++ -Wall -g -c card.cpp

clean:
	rm -f *.o main

