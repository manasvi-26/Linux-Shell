#include "headers.h"

void piping(char *string)
{
    char *arg[50];

    char *token;
    token = strtok(string,"|");

    int pt = 0;
    while(token != NULL)
    {
        arg[pt] = token;
        pt++;
        token = strtok(NULL,"|");
    }

    arg[pt] = NULL;


    int restore_stdout = dup(STDOUT_FILENO);
    int restore_stdin = dup(STDIN_FILENO);
    
    
    int fd[2];
    for(int i=0;i<pt;i++)
    {
        pipe(fd);

        pid_t pid = fork();
        if(pid == 0)
        {
            close(fd[0]); 

            //if(i != pt - 1)dup2(fd[1],1); 
            if(i == pt -1)dup2(restore_stdout,1);
            else dup2(fd[1],1);
            
            //dup2(input,STDIN_FILENO);

            execute(arg[i]);
            close(fd[1]);

            exit(0);
        }
        else if(pid > 0)
        {
            close(fd[1]);
            wait(NULL);

            //input = fd[0];
            dup2(fd[0],0);
            close(fd[0]);
        }       
    }

    dup2(restore_stdin,0);
    dup2(restore_stdout,1);

}