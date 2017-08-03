#include "pipes.h"
#include "../tokenize/makeArgs.h"

int containsPipe(char *s)
{
	int total = 0;
	int x;
	for(x = 0; x < strlen(s); x++)
	{
		if(s[x] == '|')
			total++;
	}//end for
	//printf("Number of pipes are: %d\n",total);
	return total;
}//end method


char ** parsePrePipe(char *s, int * preCount)
{
	char* saveptr;
	char* token;
	char** temp;
	char copy[100];
	strcpy(copy,s);
	token = strtok_r(copy,"|",&saveptr);
	*preCount = makeargs(token,&temp);
	//printf("PrePipe: ");
	int x;
	for(x = 0; x < *preCount; x++)
	{
		printf("%s",temp[x]);
	}//end for
	printf("\n");
	return temp;
}//end method


char ** parsePostPipe(char *s, int * postCount)
{
	char* saveptr;
	char* token;
	char** temp;
	char copy[100];
	strcpy(copy,s);
	strtok_r(copy,"|",&saveptr);
	token = strtok_r(NULL,"",&saveptr);
	*postCount = makeargs(token,&temp);
	//printf("PostPipe: ");
	int x;
	for(x = 0; x < *postCount; x++)
	{
		printf("%s",temp[x]);
	}//end for
	printf("\n");
	return temp;
}//end method


void pipeIt(char ** prePipe, char ** postPipe)
{
	//One and Done
/*
	pid_t pid;
	int fd[2], res, status;

	res = pipe(fd);

	if(res < 0)
	{
		printf("Pipe Failure\n");
		exit(-1);
	}// end if

	pid = fork();

	if(pid != 0)
	{
   		close(fd[1]);
		dup2(fd[0],0);
		close(fd[0]);
		execvp(postPipe[0], postPipe);
		exit(-1);
	}// end if 
	else
	{
		close(fd[0]);
		close(1);
		dup(fd[1]);
		close(fd[1]);
		execvp(prePipe[0], prePipe);
		exit(-1);
	}// end else 
*/
	//Fixed PipeIt

	pid_t pid = 0;
	pid_t pid2 = 0;
	int fd[2], res, status;
	pid2 = fork();
	if(pid2 != 0)
		waitpid(pid2, &status, 0);
	else
	{
		res = pipe(fd);
		if(res < 0)
		{
			printf("Pipe Failure\n");
			exit(-1);
		}// end if

		pid = fork();

		if(pid != 0)
		{
			close(fd[1]);
			dup2(fd[0],0);
			close(fd[0]);
			execvp(postPipe[0], postPipe);
			printf("Invalid command in post pipe\n");
			exit(-1);
		}// end if 

		else
		{
			close(fd[0]);
			close(1);
			dup(fd[1]);
			close(fd[1]);
			execvp(prePipe[0], prePipe);
			printf("Invalid command in pre pipe\n");
			exit(-1);
		}// end else

	}//end else

}//end method
