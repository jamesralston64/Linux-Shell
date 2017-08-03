#include "history.h"
#include "../utils/myUtils.h"

static int count = 1;

int getHistCount(FILE * fin, char * s)
{
	fgets(s, MAX, fin);
	strip(s);
	char delimiter[]= "=";
	char * temp = strtok(s, delimiter);
	int num = atoi(s);
	return num;
}//end method

int getHistFileCount(FILE * fin, char * s)
{
	char * ptr;
	fgets(s, MAX, fin);
	strip(s);
	char delimiter[] = "=";
	char * temp= strtok_r(s, delimiter, &ptr);
	int num = atoi(ptr);
	return num;
}//end method

void printListHistory(const LinkedList * theList, void (*convertData)(void *), int num)
{
	if(theList -> size == 0)
	{
		printf("Empty List\n");
	}//end if
	else
	{
		Node * cur = theList -> head -> next;
		if(num > 0)
		{
			int i;
			for(i = 0; i < num; i++)
			{
				cur = cur -> next;
			}//end for
		}//end if
		while(cur != NULL)
		{
			convertData(cur -> data);
			cur = cur -> next;
		}
		printf("\n");
	}
}//end printList

void * buildHistory(char* s, int argc, char** argv)
{
	if(argc == 0 || s == NULL)
		exit(-99);

	history * historyList = (history *)calloc(1, sizeof(history));
	historyList -> data = (char *)calloc(strlen(s) + 1, sizeof(char));
	strcpy(historyList -> data, s);
	historyList -> argv = argv;
	historyList -> argc = argc;
	return historyList;

}//end method

void cleanHistory(void * ptr)
{
	history * temp = (history*)ptr;
	int i;
	for(i = 0; i < temp -> argc; i++)
	{
		free(temp -> argv[i]);
		temp -> argv[i] = NULL;
	}//end for

	free(temp -> data);
	temp -> data = NULL;
	free(temp -> argv);
	temp -> argv = NULL;
	temp -> argc = 0;
	free(temp);
	temp = NULL;
}//end method

void printHistory(void * passedIn)
{
	history* temp = (history*)passedIn;
	printf("%s\n", temp->data);
}//end method
