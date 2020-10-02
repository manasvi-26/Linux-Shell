#include "headers.h"

void get_job(char *string,int type)
{
    
    if(string == NULL)
    {
        face = 0;
        printf("Enter job number\n");
        return;
    }

    char *token;
    token = strtok(string," \t\n");

    if(token == NULL)
    {
        face = 0;
        printf("Enter job number\n");
        return;
    }

    int job_number = atoi(token);

    if(job_number >= process_cnt)
    {
        face = 0;
        printf("Invalid job number : %d \n",job_number);
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

            if(type)
            {
                face = 0;
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
    ForeProc.pid = pid;
   
    printf("[%d]   running    %s \n,",job_number,name);

    
    kill(pid,SIGCONT);

    signal(SIGTTIN,SIG_IGN);
    signal(SIGTTOU,SIG_IGN);

    //signal(SIGTSTP,ctrlz_handler);
    
    tcsetpgrp(STDIN_FILENO,pid);

    int status;
    waitpid(pid,&status,WUNTRACED);

    //check if process has been stoppped by a signal(ctrl Z):
    if(WIFSTOPPED(status))
    {
        printf("[%d]   suspended    %s\n",job_number,name);
    }
    else if(WIFEXITED(status))
    {
        face = 1;
        Delete(pid);
    }
    else if(!WIFEXITED(status))
    {
        face = 0;
        Delete(pid);
    }



    int shell_pgrp = getpgrp();
    tcsetpgrp(STDIN_FILENO,shell_pgrp);
    
    signal(SIGTTIN,SIG_DFL);
    signal(SIGTTOU,SIG_DFL);
    return;

}

