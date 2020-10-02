#include "headers.h"

void kjob(char *string)
{
    char*token;

    char *arg[5];
    token = strtok(string," \t\n");

    int p = 0;
    while(token != NULL)
    {
        arg[p] = token;
        token = strtok(NULL," \t\n");
        p++;
    }

    arg[p] = NULL;

    if(p == 2)
    {
        int job_number = atoi(arg[0]);
        int signal = atoi(arg[1]);

        if(job_number >= process_cnt)
        {
            face = 0;
            printf("Invalid job number - %d \n",job_number);
            return;
        }
        int counter = 0;
        for(int i=0;i<1024;i++)
        {
            if(bg_process[i].pid != -1)counter++;
            if(counter == job_number)
            {
                int check = kill(bg_process[i].pid,signal);
                if(check == -1)
                {
                    face = 0;
                    perror("Error");
                }
                process_cnt--;
                bg_process[i].pid = -1;
                break;
            }
        }
    }
    else
    {
        face = 0;
        RED printf("Supunde : Invalid Syntax\n");reset();
        Magenta printf("Usage : ");reset();
        printf("kjob <job number> <signal number>\n");
    }
    
}