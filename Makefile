ush:	cscd340Lab6.c ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./linkedlist/listUtils.o ./linkedlist/linkedList.o ./history/history.o ./redirect/redirect.o
	gcc -g cscd340Lab6.c ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./linkedlist/listUtils.o ./linkedlist/linkedList.o ./history/history.o ./redirect/redirect.o -o ush

myUtils.o:	./utils/myUtils.c ./utils/myUtils.h
	gcc -g -c ./utils/myUtils.c

process.o:	./process/process.c ./process/process.h
	gcc -g -c ./process/process.c

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	gcc -g -c ./pipes/pipes.c

listUtils.o:	./linkedlist/listUtils.c ./linkedlist/listUtils.h
		gcc -g -c ./linkedlist/listUtils.c

linkedList.o:	./linkedlist/linkedList.c ./linkedlist/linkedList.h
		gcc -g -c ./linkedlist/linkedList.c

history.o:	./history/history.c ./history/history.h
	gcc -g -c ./history/history.c

redirect.o:	./redirect/redirect.c ./redirect/redirect.h
	gcc -g -c ./redirect/redirect.c

clean:
	rm ./pipes/pipes.o
	rm ./linkedlist/listUtils.o
	rm ./linkedlist/linkedList.o
	rm ./utils/myUtils.o
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./history/history.o
	rm ./redirect/redirect.o
	rm ush
