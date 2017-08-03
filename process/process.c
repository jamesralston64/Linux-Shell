#include "process.h"

void forkIt(char ** argv)
{
  int status;
  pid_t pid = fork();

  if(pid == 0)
  {
    execvp(*argv, argv);
    exit(-1);
  }//end if
  else
  {
    waitpid(pid, &status, 0);
  }//end else
}//end forkIt
