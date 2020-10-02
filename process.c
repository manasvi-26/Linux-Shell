#include "headers.h"

void foreground(char *arg[]);
void background(char *arg[]);

void get_command(char *string)
{
    char *arg[256];

    char *token;
    char delimeters[] = "\t\n\r ";
    token = strtok(string, delimeters);

    int pt = 0;

    while (token != NULL)
    {
        arg[pt] = token;
        token = strtok(NULL, delimeters);
        pt++;
    }
    arg[pt] = NULL;

    //printf("%d",pt);

    if (!strcmp(arg[pt - 1], "&"))
    {
        arg[pt - 1] = NULL;
        background(arg);
    }
    else
    {
        foreground(arg);
    }
}

void Delete(int pid)
{
    for (int i = 0; i < 1024; i++)
    {
        if (bg_process[i].pid == pid)
        {
            process_cnt--;
            strcpy(bg_process[i].p_name, "");
            bg_process[i].pid = -1;  
            return;
        }
    }
}

void foreground(char *arg[])
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        printf("ERROR: Forking child process failed \n");
        exit(EXIT_FAILURE);
        return;
    }
    if (pid == 0) //child process
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);

        setpgid(0, 0);

       
        int check = execvp(arg[0], arg);

        if (check < 0)
        {
            fprintf(stderr, "supunde: command not found: %s\n", arg[0]);
            exit(EXIT_FAILURE);
        }

        exit(0);
    }
    if (pid > 0)
    {
        ForeProc.pid = pid;
        bg_process[job].pid = pid;
        strcpy(bg_process[job].p_name, arg[0]);
        job++;
        process_cnt++;

        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);

        //signal(SIGTSTP,ctrlz_handler);

        tcsetpgrp(STDIN_FILENO, pid);

        strcpy(ForeProc.p_name, arg[0]);
        int status;
        waitpid(pid, &status, WUNTRACED);        

        if(WIFSTOPPED(status))
        {
            face = 0;
        }        
        //else Delete(pid,status);
        else if(WIFEXITED(status) && !(WEXITSTATUS(status)))
        {
            face = 1;
            Delete(pid);
        }
        else
        {
            face = 0;
            Delete(pid);
        }
        
        int shell_pgrp = getpgrp();
        tcsetpgrp(STDIN_FILENO, shell_pgrp);

        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
    }
}

void background(char *arg[])
{
    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        printf("ERROR: Forking child process failed \n");
        exit(EXIT_FAILURE);
        return;
    }

    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);

        setpgid(0, 0);

        int check = execvp(arg[0], arg);
        if (check < 0)
        {
            fprintf(stderr, "supunde: command not found: %s\n", arg[0]);
            exit(EXIT_FAILURE);
        }

        exit(0);
    }
    if (pid > 0)
    {
        printf("[%d]  %d   %s\n", process_cnt, pid, arg[0]);

        bg_process[job].pid = pid;
        strcpy(bg_process[job].p_name, arg[0]);
        job++;

        process_cnt++;
        return;
    }
}
