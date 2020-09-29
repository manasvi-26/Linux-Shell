#include "headers.h"

void foreground(char* arg[]);
void background(char *arg[]);

void get_command(char *string)
{
    char* arg[256];
  
    char*token;
    char delimeters[] = "\t\n\r ";
    token = strtok(string,delimeters);
    

    int pt = 0;
   
    while(token != NULL)
    {
        arg[pt] = token;
        token = strtok(NULL,delimeters);
        pt++; 
    }
    arg[pt] = NULL;
    
    //printf("%d",pt);
    
    if(!strcmp(arg[pt-1],"&"))
    {
        arg[pt-1] = NULL;
        background(arg);
    }
    else
    {
        foreground(arg);
    }
}

void foreground(char *arg[])
{
    pid_t pid;
    pid = fork();
    if(pid < 0)
    {
        printf("ERROR: Forking child process failed \n");
        return;
        
    }
    if(pid == 0)   //child process
    {
        int check = execvp(arg[0],arg);
        
        if(check < 0)
        {
            fprintf(stderr,"supunde: command not found: %s\n",arg[0]);   
        }

        exit(0);
    }
    if(pid > 0)
    {
        ForeProc.pid = pid;
        strcpy(ForeProc.p_name,arg[0]);

        waitpid(pid,NULL,WUNTRACED);
        ForeProc.pid = 0;
    }       
}

void background(char *arg[])
{
    pid_t pid;
    pid = fork();

    if(pid < 0)
    {
        printf("ERROR: Forking child process failed \n");
        return;
    }

    if(pid == 0)
    {
        setpgid(0,0);
        

        int check =  execvp(arg[0],arg);
        if(check < 0)
        {
            fprintf( stderr, "supunde: command not found: %s\n",arg[0]);
        }

        exit(0);
    } 
    if(pid > 0)
    {
        printf("[%d]  %d   %s\n",process_cnt,pid,arg[0]);

        bg_process[job].pid = pid;
        strcpy(bg_process[job].p_name,arg[0]);
        job++;

        process_cnt++;
        return;
    }
}

