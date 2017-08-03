#include "listUtils.h"

Node * buildNode(FILE * fin, void *(*buildData)(FILE * in) )
{
	Node * newNode = (Node *)calloc(1,sizeof(Node));
	newNode->data = buildData(fin);
	return newNode;
}//end method

Node * buildNode_Type(void * passedIn)
{
	Node * newNode = (Node *)calloc(1,sizeof(Node));
	newNode->data = passedIn;
	return newNode;
}//end method

void sort(LinkedList * theList, int (*compare)(const void *, const void *))
{
	if(theList == NULL)
	{
		printf("List is Empty");
		exit(-99);
	}//end if

	else if(theList->size == 1)
		return;
	else 
	{
		Node * x, * y, * smallest;
		void * temp;
		for(x = theList -> head -> next; x != NULL; x = x -> next) 
		{
			smallest = x;
			for(y = x; y != NULL; y = y -> next) 
			{
				if (compare(smallest -> data,y -> data) > 0) 
				{
					smallest = y;
			    	}//end if
			}//end inner for
			temp = x -> data;
			x -> data = smallest -> data;
			smallest -> data = temp;
		}//end outer for
	}//end else
}//end method

void buildListTotal(LinkedList * myList, int total, FILE * fin, void * (*buildData)(FILE * in))
{
	if(myList == NULL)
	{
		printf("List is Empty");
		exit(-99);
	}//end if

	else if(total <= 0) 
	{
		printf("List total is empty");
		exit(-99);	
	}//end else if

	else 
	{
		
		int x;
		for (x = 0; x < total; x++)
		{
			void * temp = buildData(fin);
			Node * newNode = (Node *)calloc(1,sizeof(Node));
			newNode -> data = temp;
			addFirst(myList,newNode);
		}//end for
		myList -> size = total;
	}//end else
}//end method
