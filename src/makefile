all main.o singleLinkedList.o:
	gcc -c main.c -lpthread -o ../bin/main.o
	gcc -c singleLinkedList.c -lpthread -o ../bin/singleLinkedList.o
	gcc -o ../bin/main.out ../bin/main.o ../bin/singleLinkedList.o



allDB:
	gcc -g -c main.c -lpthread -o ../bin/main.o
	gcc -g -c singleLinkedList.c -lpthread -o ../bin/singleLinkedList.o
	gcc -g -o ../bin/main.out ../bin/main.o ../bin/singleLinkedList.o


clean:
	rm -rf *.o 
	rm -rf main
	rm -rf ../bin/*.o
	rm -rf ../bin/main 