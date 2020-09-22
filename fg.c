#include "headers.h"

void fg(char *string)
{
    char *token;
    token = strtok(string," \t\n");

    if(token == NULL)
    {
        printf("Enter job number\n");
        return;
    }

    int job_number = atoi(token);

    if(job_number >= process_cnt)
    {
        printf("Invalid job number - %d \n",job_number);
        return ;
    }

    int counter = 1;
    int pid;
    char*name;
    for(int i=0;i<1024;i++)
    {
        if(bg_process[i].pid != -1)counter++;
        if(counter == job_number)
        {
            name = bg_process[i].p_name;
            pid = bg_process[i].pid;
            break;
        }  
    }

    






    




}