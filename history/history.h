#ifndef HISTORY_H
#define HISTORY_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tokenize/makeArgs.h"
#include "../linkedlist/linkedList.h"

#define MAX 100

struct hist
{
    	 int argc;
    	 char ** argv;
	     char * data;
    	  int num;
};

typedef struct hist history;

int getHistCount(FILE * fp, char * s);
int getHistFileCount(FILE * fp, char * s);
void * buildHistory(char * s, int argc, char **argv);
void printHistory(void * passedIn);
void cleanHistory(void * ptr);
void printListHistory(const LinkedList * theList, void (*convertData)(void *), int num);


#endif
