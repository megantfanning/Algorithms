default: prog

dynamicArray.o: dynamicArray.c dynamicArray.h 
	gcc -Wall -std=c99 -c dynamicArray.c

Algos.o: Algos.c Algos.h 
	gcc -Wall -std=c99 -c Algos.c		
	
UserInt.o: UserInt.c UserInt.h 
	gcc -Wall -std=c99 -c UserInt.c	

prog: dynamicArray.o Algos.o UserInt.o main.c
	gcc -Wall -std=c99 -o prog dynamicArray.o Algos.o UserInt.o main.c -lm
		
clean:
	rm dynamicArray.o
	rm Algos.o

cleanall: clean
	rm prog
	rm Results.txt
	rm Experiment.txt
