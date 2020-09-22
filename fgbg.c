#include "headers.h"

void get_job(char *string,int type)
{
    if(string == NULL)
    {
        printf("Enter job number\n");
        return;
    }

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

    int counter = 0;
    int pid;
    char name[50];

    
    for(int i=0;i<1024;i++)
    {
        if(bg_process[i].pid != -1)counter++;
        if(counter == job_number)
        {
            strcpy(name, bg_process[i].p_name);
            pid = bg_process[i].pid;

            bg_process[i].pid = -1;
            process_cnt--;
            if(type)
            {
                fg(job_number,pid,name);
            }
            else
            {
                kill(pid,SIGCONT);
            } 
            break;
        }  
    }
}



void fg(int job_number,int pid, char *name)
{
   
    printf("[%d]   running    %s\n",job_number,name);

    signal(SIGTTIN,SIG_IGN);
    signal(SIGTTOU,SIG_IGN);
    tcsetpgrp(STDOUT_FILENO,pid);

    kill(pid,SIGCONT);
    
    int status;
    waitpid(pid,&status,WUNTRACED);

    //check if process has been stoppped by a signal(ctrl Z):
    if(WIFSTOPPED(status))
    {
        printf("[%d]   suspended    %s",job_number,name);
        process_cnt++;
        strcpy(bg_process[job].p_name,name);
        bg_process[job].pid = pid;
        job++;
    }


    int shell_pgrp = getpgrp();
    tcsetpgrp(STDOUT_FILENO,shell_pgrp);
    signal(SIGTTIN,SIG_DFL);
    signal(SIGTTOU,SIG_DFL);
    return;

}

