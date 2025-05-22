# Machine Learning AI, Game of Nim
# open the file unsafe to mark unsafe moves, this file can be opened in a main method 
# and then be used in methods called by it
import random
def main():
      print("Enter the number of chips in each pile (A B C): ")
      a = (int(input()))
      b = (int(input()))
      c = (int(input()))
      while(a < 0 or b < 0 or c < 0):
        print("Non positive number of chips detected. Please enter the number of chips again (A B C): ")
        a = (int)(input())
        b = (int)(input())
        c = (int)(input())
      print("The number chips in each pile initially\nA: ", a, "\tB: ", b,"\tC: ", c)
      play(a,b,c)
      

def printBoard(a,b,c):
    print("The number chips in each pile\nA: ", a, "\tB: ", b,"\tC: ", c)

def play(a,b,c):
    prevA = a
    prevB = b
    prevC = c
    print("Type 0 if you want the MACHINE to start, and 1 if YOU want to start: ")
    choice = input()
    if(choice == "1"):
        player = "player"
        while(isWin(a,b,c,player) != 0):
            player = "player"
            chosenPile = "x"
            sub = 0
            print("Enter the pile letter (A, B, C) and the number of chips to remove: ")
            chosenPile = input()
            sub = input()
            if(chosenPile.lower() == "a"):
                print("The human will take ", sub, " chip(s) from pile A.")
                a -= int(sub)
            elif(chosenPile.lower() == "b"):
                print("The human will take ", sub, " chip(s) from pile B.")
                b -= int(sub)
            elif(chosenPile.lower() == "c"):
                print("The human will take ", sub, " chip(s) from pile C.")
                c -= int(sub)
            printBoard(a,b,c)
            
            player = "computer"
            a,b,c = decision(a, b, c)
            printBoard(a,b,c)
            prevA = a
            prevB = b
            prevC = c


        printBoard(a,b,c)

    elif(choice == "0"):
        player = "computer"
        while(isWin(a,b,c,player) != 0):
            prevA = a
            prevB = b
            prevC = c
            player = "computer"
            a, b, c = decision(a,b,c)
            printBoard(a,b,c)
            if(isWin(a,b,c,player) != 0):
                prevA = a
                prevB = b
                prevC = c
                player = "player"
                chosenPile = "x"
                sub = 0
                print("Enter the pile letter (A, B, C) and the number of chips to remove: ")
                chosenPile = input()
                sub = input()
                if(chosenPile.lower() == "a"):
                    print("The human will take ", sub, " chip(s) from pile A.")
                    a -= int(sub)
                elif(chosenPile.lower() == "b"):
                    print("The human will take ", sub, " chip(s) from pile B.")
                    b -= int(sub)
                elif(chosenPile.lower() == "c"):
                    print("The human will take ", sub, " chip(s) from pile C.")
                    c -= int(sub)
                printBoard(a,b,c)
            
    learn(prevA,prevB,prevC)
           
def quickLearn():
    player = "computer"
    for i in range(500):
        a = random.randrange(100)
        b = random.randrange(100)
        c = random.randrange(100)
        prevA = a
        prevB = b
        prevC = c
        while(isWin(a,b,c,player) != 0):
            prevA = a
            prevB = b
            prevC = c
            player = "computer"
            a, b, c = decision(a,b,c)
            printBoard(a,b,c)
            prevA = a
            prevB = b
            prevC = c
            choosePile = random.randrange(1,3,1)
            if(choosePile == 1):
                a -= random.randrange(1,3,1)
                while(a < 0):
                    a += 1
            elif(choosePile == 2):
                b -= random.randrange(1,3,1)
                while(b < 0):
                    b += 1
            elif(choosePile == 3):
                c -= random.randrange(1,3,1)
                while(c < 0):
                    c += 1
            
       

def isWin(a, b, c, player):
    if(a == 0 and b == 0 and c == 0):
        print(player," loses")
        return 0
    else:
        return 1
    

def decision(a, b, c):
    # Setting up temp variables to check against the file without editing the actual piles
    x = a
    y = b
    z = c
    #decision making process. If a choice is in the file don't make it. Start with x -= 3 ....
    if(check(x - 3, y , z) != True and a>=3):
        a -= 3
        print("The computer will take 3 chip(s) from pile A.")
    elif(check(x, y-3, z) != True and b>=3):
        b -= 3
        print("The computer will take 3 chip(s) from pile B.")
    elif(check(x , y , z-3) != True and c>=3):
        c -= 3
        print("The computer will take 3 chip(s) from pile C.")
    elif(check(x -2, y , z) != True and a>=2):
        a -= 2
        print("The computer will take 2 chip(s) from pile A.")
    elif(check(x,y-2,z) != True and b>=2):
        b -= 2
        print("The computer will take 2 chip(s) from pile B.")
    elif(check(x,y,z-2)!=True and c>= 2):
        c -=2
        print("The computer will take 2 chip(s) from pile A.")
    elif(check(x-1,y,z)!=True and a>=1):
        a-=1
        print("The computer will take 1 chip(s) from pile A.")
    elif(check(x,y-1,z)!=True and b>=1):
        b-=1
        print("The computer will take 1 chip(s) from pile A.")
    elif(check(x,y,z-1)!=True and c>=1):
        c-=1
        print("The computer will take 1 chip(s) from pile A.")
    else:
        if(a >= 3):
            a -= 3
            print("The computer will take 3 chip(s) from pile A.")
        elif(b >= 3):
            b -=3
            print("The computer will take 3 chip(s) from pile B.")
        elif(c >= 3):
            c -= 3
            print("The computer will take 3 chip(s) from pile C.")
        elif(a >= 2):
            a -= 2
            print("The computer will take 2 chip(s) from pile A.")
        elif(b >= 2):
            b -= 2
            print("The computer will take 2 chip(s) from pile B.")
        elif(c >= 2):
            c -= 2
            print("The computer will take 2 chip(s) from pile C.")
        elif(a >= 1):
            a -= 1
            print("The computer will take 1 chip(s) from pile A.")
        elif(b >= 1):
            b -= 1
            print("The computer will take 1 chip(s) from pile B.")
        elif(c >= 1):
            c -=1
            print("The computer will take 1 chip(s) from pile C.")
    if(isWin(a,b,c,"computer") == 0 and check(x,y,z) == False):
        learn(x,y,z)
    return a,b,c

    
def check(x, y, z):
    inp = "{} {} {}".format(x,y,z)
    with open("unsafe") as f:
        unsafeFile = f.readlines()
    for line in unsafeFile:
        if inp in line:
            return True   
    return False

def learn(prevA, prevB, prevC):
    f = open("unsafe", "a")
    f.write(str(prevA+1) + " " + str(prevB) + " " + str(prevC) + "\n")
    f.write(str(prevA) + " " + str(prevB+1) + " " + str(prevC) + "\n")
    f.write(str(prevA) + " " + str(prevB) + " " + str(prevC+1) + "\n")
    f.write(str(prevA+2) + " " + str(prevB) + " " + str(prevC) + "\n")
    f.write(str(prevA) + " " + str(prevB+2) + " " + str(prevC) + "\n")
    f.write(str(prevA) + " " + str(prevB) + " " + str(prevC+2) + "\n")
    f.write(str(prevA+3) + " " + str(prevB) + " " + str(prevC) + "\n")
    f.write(str(prevA) + " " + str(prevB+3) + " " + str(prevC) + "\n")
    f.write(str(prevA) + " " + str(prevB) + " " + str(prevC+3) + "\n")
    f.close()


# main function. might not be necessary but a habit from c++ and java
main()
