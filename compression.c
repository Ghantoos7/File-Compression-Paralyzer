#include "headers.h"

int parrarel_compression_all(const char *folderPath)
{
    int filesCount = countFiles(folderPath);
    char **filesList = listFiles(folderPath);

    int T1 = time(NULL);

    for (int i = 0; i < filesCount; i++)
    {
        int value = fork();

        if (value == -1)
        {
            printf("Error\n");
            exit(0);
        }

        else if (value == 0)
        {
            char command[256];
            sprintf(command, "gzip -k -f %s", filesList[i]);
            system(command);
            exit(0);
        }
    }

    for (int i = 0; i < filesCount; i++)
    {
        wait(NULL);
    }
    int T2 = time(NULL);
    return T2 - T1;
}



int parallel_compression_cores(const char *folderPath, int NB_CORES)
{
    int filesCount = countFiles(folderPath);
    char **filesList = listFiles(folderPath);

    int T1 = time(NULL);

    for (int i = 0; i < filesCount; i += NB_CORES)
    {
        int end = i + NB_CORES;
        if (end > filesCount)
        {
            end = filesCount;
        }

        for (int j = i; j < end; j++)
        {
            int value = fork();

            if (value == -1)
            {
                printf("Error\n");
                exit(1);
            }
            else if (value == 0)
            {
                char command[256];
                sprintf(command, "gzip -k -f %s", filesList[j]);
                system(command);
                exit(0);
            }
        }

        for (int j = i; j < end; j++)
        {
            wait(NULL);
        }
    }

    int T2 = time(NULL);
    return T2 - T1;
}



int main(int argc, char **argv)
{

    removeGzFiles(argv[1]);

    printf("it took %d seconds to compres all those files (parralizing all)\n" , parrarel_compression_all(argv[1]));

   
    return 0;
}