default: TSP

Algos.o: Algos.c Algos.h 
	gcc -Wall -std=c99 -c -lm Algos.c		
	
UserInt.o: UserInt.c UserInt.h 
	gcc -Wall -std=c99 -c UserInt.c	

TSP: Algos.o UserInt.o Main.c
	gcc -Wall -std=c99 -o TSP Algos.o UserInt.o Main.c 
		
clean:
	rm userInt.o
	rm Algos.o

cleanall: clean
	rm TSP
