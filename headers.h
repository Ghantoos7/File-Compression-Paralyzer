#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
# include <sys/wait.h>


int getNumCPUs();
int countFiles(const char *folderPath);
char ** listFiles(const char *folderPath);
void removeGzFiles(const char *folderPath);

