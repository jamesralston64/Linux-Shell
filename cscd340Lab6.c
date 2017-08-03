/*
*  Created by James
*/

#include "./linkedlist/listUtils.h"
#include "./linkedlist/linkedList.h"
#include "./tokenize/makeArgs.h"
#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./history/history.h"

#include "./redirect/redirect.h"


int main()
{
  	 int argc;
     int pipeCount;
     int histCount;
     int histFileCount;
     int preCount = 0;
     int postCount = 0;
     FILE * hist = NULL;
     char * path;
	   char * ptr;
  	 char ** argv;
     char ** preRedirect;
     char ** postRedirect;
     char s[MAX];
     char tempLine[MAX];
	   char input[MAX];
  	 char ** prePipe = NULL;
     char ** postPipe = NULL;
	   LinkedList * histList = linkedList();

	if(access(".msshrc", F_OK) != -1)
	{
		FILE * fin = fopen(".mshrc", "r");
		histCount = getHistCount(fin, s);
		histFileCount = getHistFileCount(fin, s);

		while(fgets(tempLine, MAX, fin))
		{
      if(strstr(tempLine, "PATH=") != NULL)
			{
				strip(tempLine);
				strtok_r(tempLine, ":", &ptr);
				path = strtok_r(NULL, "\0", &ptr);
				setenv("PATH", path, 1);
			}//end if

		}//end while

		fclose(fin);
	}//end if

	histCount = 100;
	histFileCount = 1000;

	hist = fopen(".mshrc_history", "r");
	if(hist != NULL)
	{
		while (fgets(input, MAX, hist))
		{
			strip(input);
			argc = makeargs(input, &argv);
			addLast(histList, buildNode_Type(buildHistory(input, argc, argv)));

		}//end while

		fclose(hist);

	}//end if

	printf("command?: ");
	fgets(s, MAX, stdin);
	strip(s);

	while(strcmp(s, "exit") != 0)
	{
    if(strcmp(s, "history") == 0)
		{
      int total;
			total = histList -> size - histCount;
			printListHistory(histList, printHistory, total);
		}//end if

		if(strncmp(s, "cd ", 3) == 0)
		{
			char * cdtemp = &(s[3]);
			chdir(cdtemp);
		}//end if

    else if(containsRedirection(s) != 0)
		{
			preRedirect = preRedirection(s, &preCount);
			postRedirect = postRedirection(s, &postCount);
			redirection(preRedirect, postRedirect, s);
			clean(preCount, preRedirect);
      clean(postCount, postRedirect);
		}//end elseif


		else if(pipeCount > 0)
		{
			prePipe = parsePrePipe(s, &preCount);
			postPipe = parsePostPipe(s, &postCount);
			pipeIt(prePipe, postPipe);
			clean(preCount, prePipe);
			clean(postCount, postPipe);
		}// end else if


		else if(s[1] == '!')
		{
			if(strcmp(s, "!!") == 0)
			{
				if(histList -> size == 0)
				{
					printf("History is empty\n");
				}//end if

				else
        {
          Node * curr = histList -> head;

					int i;
					for(i = 0; i < histList -> size; i++)
          {
						curr = curr -> next;
          }//end for

					history * temp = (history *)curr -> data;
					strcpy(s, temp -> data);
					strip(s);
        }//end else

			}//end if(s[1] == !)

			else
			{
				if(histList -> size == 0)
				{
					printf("History is empty\n");
				}//end if
				else
        {
          strip(s);
					memmove(s, s + 1, strlen(s));

					int total;
					total = atoi(s);
					if(total < histList -> size)
					{

						Node * curr = histList -> head;
						int i;
						for(i = 0; i < total; i++)
            {
							curr = curr -> next;
            }//end for

						history * tempHistory = (history*)curr -> data;
						strcpy(s, tempHistory -> data);
						strip(s);
					}//end if

        }//end else

			}//end else

			argc = makeargs(s, &argv);
			if(argc != -1)
		  	{
		  		forkIt(argv);
		  		clean(argc, argv);
		  		argv = NULL;
			}// end if

		}//end else if

		else
		{
			argc = makeargs(s, &argv);
		  	if(argc != -1)
		  	{
		  		forkIt(argv);
		  		clean(argc, argv);
		  		argv = NULL;
			}// end if
		}//end else

		addLast(histList, buildNode_Type(buildHistory(s, argc, argv)));

		printf("command?: ");
		fgets(s, MAX, stdin);
	  strip(s);
	}// end while

	addLast(histList, buildNode_Type(buildHistory(s, argc, argv)));
	hist = fopen(".mshrc_history", "w");

	if(hist != NULL)
	{
		if(histList -> size != 0)
		{
			Node * curr = histList -> head -> next;
			history * temp;
			if(histFileCount < histList -> size)
			{
				int i;
				for(i = 0; i < histList -> size - histFileCount; i++)
        {
					curr = curr -> next;
        }//end for

			}//end if
			while(curr != NULL)
			{
				temp = (history*)curr -> data;
				fprintf(hist, "%s\n", temp -> data);
				curr = curr -> next;
			}//end while

		}//end if

	}//end if

	fclose(hist);

	clearList(histList, cleanHistory);
	free(histList);
	histList = NULL;

	return 0;

}// end main
