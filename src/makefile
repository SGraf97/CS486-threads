all main.o singleLinkedList.o:
	
	gcc  -lpthread singleLinkedList.c -c  -o ../bin/singleLinkedList.o
	gcc  -lpthread main.c -c  -o ../bin/main.o
	gcc  -lpthread UnboundedQueue.c -c  -o ../bin/queue.o  
	gcc  -lpthread trees.c -c -o ../bin/trees.o
	gcc  -lpthread  -o ../bin/main.out ../bin/main.o ../bin/singleLinkedList.o ../bin/queue.o ../bin/trees.o



allDB:
	
	gcc  -lpthread -g -c main.c -lpthread -o ../bin/main.o
	gcc  -lpthread -g -c singleLinkedList.c -lpthread -o ../bin/singleLinkedList.o
	gcc  -lpthread -g UnboundedQueue.c -c  -o ../bin/queue.o  
	gcc  -lpthread -g trees.c -c -o ../bin/trees.o
	gcc  -lpthread -g -o ../bin/main.out ../bin/main.o ../bin/singleLinkedList.o ../bin/queue.o ../bin/trees.o


tester: all
	gcc tester.c -o ../bin/tester
	../bin/tester 
	code testlog


clean:
	rm -rf *.o 
	rm -rf main
	rm -rf ../bin/*.o
	rm -rf ../bin/main 
	rm -rf ./testlog
	rm -rf ../bin/main.out
	rm -rf ../bin/tester
	