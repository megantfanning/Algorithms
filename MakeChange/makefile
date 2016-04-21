default: Change

dynamicArray.o: dynamicArray.c dynamicArray.h 
	gcc -Wall -std=c99 -c dynamicArray.c

Algos.o: Algos.c Algos.h 
	gcc -Wall -std=c99 -c Algos.c		
	
UserInt.o: UserInt.c UserInt.h 
	gcc -Wall -std=c99 -c UserInt.c	

Change: dynamicArray.o Algos.o UserInt.o Main.c
	gcc -Wall -std=c99 -o Change dynamicArray.o Algos.o UserInt.o Main.c -lm
	
# Change: dynamicArray.o UserInt.o Main.c
	# gcc -Wall -std=c99 -o Change dynamicArray.o Algos.o UserInt.o Main.c -lm
		
clean:
	rm dynamicArray.o
	rm Algos.o
	rm UserInt.o

cleanall: clean
	rm Change
	rm *Change.txt
