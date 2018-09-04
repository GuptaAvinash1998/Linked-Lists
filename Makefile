#Avinash Gupta
#G01009180
#CS262, Lab Section 2B3
#Project 1

all: pro2p1 pro2p2

pro2p1: project2_agupta23_2B3_p1.c
	gcc -g -Wall -o project2_agupta23_2B3_p1 project2_agupta23_2B3_p1.c -lm

pro2p2: project2_agupta23_2B3_p2.c
	gcc -g -Wall -o project2_agupta23_2B3_p2 project2_agupta23_2B3_p2.c -lm

clean:
	rm project2_agupta23_2B3_p1
	rm project2_agupta23_2B3_p2
