#ifndef REDIRECT_H
#define REDIRECT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int containsRedirection(char *s);
char ** preRedirection(char *s, int * preCount);
char ** postRedirection(char *s, int * postCount);
void redirection(char ** prePipe, char ** postPipe, char* s);


#endif
