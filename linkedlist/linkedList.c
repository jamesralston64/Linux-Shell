#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"
#include "../history/history.h"


LinkedList * linkedList() 
{
	Node * head = (Node *)calloc(1,sizeof(Node));
	LinkedList * list = (LinkedList *)calloc(1,sizeof(LinkedList));
	list -> head = head;
	return list;
}//end method

void addLast(LinkedList * theList, Node * nn) 
{
	if(theList == NULL)
	{
		printf("The List is empty");
		exit(-99);
	}//end if

	else if(nn == NULL) 
	{
		printf("The Node is empty");
		exit(-99);
	}//end else if
	
	else if(theList->head->next == NULL)
	{
		nn -> next = theList -> head -> next; 
		nn -> prev = theList -> head; 
		theList -> head -> next = nn; 
	}//else if

	else 
	{	
		Node* cur = theList->head->next;
		while(cur->next != NULL)
		{
			cur = cur->next;
		}//end while
		nn -> next = cur -> next; 
		cur -> next = nn;
		nn -> prev = cur;
		theList -> size++;
	}//end else
}//end method

void addFirst(LinkedList * theList, Node * nn)
{

	if (theList == NULL)
		exit(-99);

	else if (nn == NULL) 
		exit(-99);

	else 
	{	
		Node * head = theList -> head;
		nn -> next = head -> next;
		head -> next = nn;
		theList -> size = theList -> size + 1;
	}
}//end method

void removeFirst(LinkedList * theList, void (*removeData)(void *))
{
	if(theList == NULL)
	{
		printf("The List is empty");
		exit(-99);
	}//end if

	else 
	{
		Node * head = theList -> head;
		Node * next = head -> next -> next;
		Node * removed = head -> next;
		head -> next = next;
		removeData(removed -> data);
		free(removed);
		removed = NULL;
		theList -> size = (theList -> size) - 1;
	}//end else
}//end method

void removeLast(LinkedList * theList, void (*removeData)(void *))
{
	if(theList == NULL)
	{
		printf("The List is empty");
		exit(-99);
	}//end if
	
	else
	{
		Node * head = theList -> head;
		Node * cur = head -> next;
		Node * prev = head;
		Node * temp;
		while(cur -> next != NULL)
		{
			prev = cur;
			cur = cur -> next;
		}//end while 
		temp = cur;
		cur = prev;
		cur -> next = NULL;
		removeData(temp -> data);
		free(temp);
		temp = NULL;
		theList -> size = (theList -> size) - 1;
	}//end else
}//end method

void removeItem(LinkedList * theList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *))
{
	void * ans = nn -> data;
	if(theList == NULL)
		exit(-99);

	else if(nn == NULL) 
		exit(-99);

	else 
	{
		Node * curr = theList -> head;
		Node * temp;
		if(curr -> next == NULL) 
			printf("List is empty");
		
		else 
		{
		    	Node * prev = theList -> head;
		    	curr = curr -> next;
		    	while(curr != NULL) 
			{
				if(compare(curr -> data,ans) == 0) 
				{
					temp = curr;
					prev -> next = curr -> next;
					curr = curr -> next;
					theList -> size = theList -> size - 1;
					removeData(temp -> data);
					free(temp);
					temp = NULL;
				}//end if
				else 
				{
					prev = prev -> next;
					curr = curr -> next;
				}//end else
		    	}//end while
		}//end else
	}//end else
	removeData(ans);
	free(nn);
	nn = NULL;
}//end method

void clearList(LinkedList * theList, void (*removeData)(void *))
{
	if(theList == NULL)
	{
		printf("The List is empty");
		exit(-99);
	}//end if

	else 
	{
		Node * cur = theList -> head -> next;
		Node * temp;
		history * hist;
		int count = 1;
		while (theList -> size > 1) 
		{
			temp = cur;
			if(cur -> next != NULL && theList -> size > 0)
			{
				cur = cur -> next;
			}//end if
			removeData(temp -> data);
			free(temp); 
			temp = NULL;
			theList -> size--;
		}//end while
		free(theList -> head);;
		theList -> head = NULL;
		theList -> size = 0;
	}//end else
}//end method

void printList(const LinkedList * theList, void (*convertData)(void *))
{
	if(theList -> size == 0)
		printf("Empty");
	else
	{
		Node * cur = theList -> head -> next;
		while(cur != NULL)
		{
			convertData(cur -> data);
			cur = cur -> next;
		}//end while
		printf("\n");
	}//end else
}//end method



