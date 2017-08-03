#include "redirect.h"
#include "../tokenize/makeArgs.c"

#define BUFFER 100

int containsRedirection(char * s)
{
	int redir = 0;

	if(strstr(s, "alias") == NULL)
	{
		int i;
		for(i = 0; i < strlen(s); i++)
		{
			if(s[i] == '>')
			{
				redir = 1;
			}//end if

		}//end for

	}//end if
	return redir;
}//end containsRedirection

char** postRedirection(char * s, int * count)
{
	char * ptr, * newWord;
	char copy[100];
	strcpy(copy, s);
	char ** temp;

	if(containsRedirection(s) == 1)
	{
		newWord = strtok_r(copy, ">", &ptr);
	}//end if

	newWord = strtok_r(NULL, "", &ptr);
	* count = makeargs(newWord, &temp);

	return temp;
}//end postRedirection

char** preRedirection(char * s, int * count)
{
	char * ptr, * newWord;
	char copy[100];
	strcpy(copy, s);
	char ** temp;

	if(containsRedirection(s) == 1)
	{
		newWord = strtok_r(copy, ">", &ptr);
	}//end if

	* count = makeargs(newWord, &temp);
	return temp;

}//end preRedirection

void redirection(char ** before, char ** after, char * s)
{
	pid_t pid = 0;
	int status;
	pid = fork();


	if(pid != 0)
		waitpid(pid, &status, 0);

	else
	{

		fflush(0);
		int fd1 = creat(* after, 0644);

		dup2(fd1, STDOUT_FILENO);
		close(fd1);
		execvp(before[0], before);

	}//end else

}//end redirection
