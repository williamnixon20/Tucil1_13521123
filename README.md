# Tugas Kecil Strategi Algoritma - Kartu 24

## General Information
A solver to the 24 puzzle, an arithmetical puzzle in which the objective is to find a way to manipulate four integers present in a card deck so that the end result is 24.  

Allowed operations include +, -, /, *, and ().

Program uses pure brute-force to try out all possibilities and permutations that evaluates to the target goal 24.

## Requirements / How to run
Program is built on c++, requiring you to have g++ installed. Program was tested using c++17.

1. Be on root directory, not src/test/doc/bin.
2. Run the following command `g++ -o bin/main src/main.cpp -lm`. This will compile the main.cpp code and put in on bin/main.
3. Execute the program by running the command `./bin/main`. Enjoy!

## How to use
If you want the cards to be generated randomly, enter 1.
If you want the cards to be manualaly inputted, enter 2.

Program accepts inputs in the form of 1-13 or A, 2-10, J, K, Q.

Program outputs the number of solution and the solutions.
Enter y/Y if you want to save the output to a file.
Enter t/T if you wanna skip the step.


## Author information
13521123 - William Nixon - K01
Teknik Informatika - ITB