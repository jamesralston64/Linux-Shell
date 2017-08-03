#include "makeArgs.h"

void clean(int argc, char **argv)
{
	int i;
	for (i = 0; i < argc; i++) 
	{
		free(argv[i]);
	}//end for
	free(argv);
}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv)
{
	char copy[MAX];
	strcpy(copy,s);
    	int total = 0;
	char * saveptr;
	char * temp;
	temp = strtok(s," ");
	while(temp != '\0')
	{
        	temp = strtok(NULL," ");
        	total++;
    	}//end while
	if(total == 0)
		return -1;
	else
	{
		strcpy(s,copy);
		(*argv) = (char**)calloc(total+1,sizeof(char*));
		temp = strtok_r(s," ",&saveptr);
		(*argv)[0] = (char*)calloc(strlen(temp)+1,sizeof(char));
		strcpy((*argv)[0],temp);
		int y;
		for(y = 1;y < total;y++)
		{
			char * temp = strtok_r(NULL," ",&saveptr);
			(*argv)[y] = (char*)calloc(strlen(temp)+1,sizeof(char));
			strcpy((*argv)[y],temp);
		}//end for
	}//end else
	return total;

}// end makeArgs
