#include "headers.h"

void interrupt(char *time)
{
    
    FILE *f;
    f = fopen("/proc/interrupts","r");
    char buffer[200] = "";
    fgets(buffer,sizeof(buffer),f);
    char*token ;
    token = strtok(buffer," \t\n");
    while(token != NULL)
    {
        printf("%s\t",token);
        token = strtok(NULL," \t\n");
    }
    printf("\n");
    fclose(f);
    while(1)
    {
        f = fopen("/proc/interrupts","r");
        
        for(int i=0;i<=2;i++)
        {
            strcpy(buffer,"");
            fgets(buffer,sizeof(buffer),f);
        }
        
        token = strtok(buffer," \t\n");
        token = strtok(NULL," \t\n");
        
        while(token != NULL)
        {
            if(token[0] == 'I')break;
            printf("%s\t",token);
            token = strtok(NULL," \t\n");
        }

        printf("\n");
        fclose(f);
        
        int n = atoi(time);
        sleep(n);
    }
    return ;
}
void newborn(char *time)
{
    FILE *f;
    char buffer[200];
    while(1)
    {
        f = fopen("/proc/loadavg","r");
        fgets(buffer,sizeof(buffer),f);

        char *token;
        token = strtok(buffer," \t\n");

        
        int pt = 0;
        while(token != NULL)
        {
            if(pt == 4)
            {
                printf("%s\n",token);
                break;
            }
            token = strtok(NULL," \t\n");
            pt++;
        }

        fclose(f);
        int n = atoi(time);
        sleep(n);
    }
}

void invalid()
{
    face = 0;
    RED printf("Invalid input\n"); reset();

    printf("Usage: nightswatch [options] <command>\n");
    
    Magenta printf("Options:\n"); reset();
    printf("-n seconds:The time interval in which to execute the command (periodically)\n");
    Magenta printf("Commands:\n"); reset();
    printf("interrupt:  Number of times CPU has been interrupted by keyboard\n");
    printf("newborn:  PID of the process that was most recently created on the system\n");
    return ;
}


void nightswatch(char * string)
{
   
    if(string == NULL)
    {
        invalid();
        return ;
    }
    char* token;
    char delimeters[] = " \t\n";

    char arg[5][200];

    token = strtok(string,delimeters);
    int pt = 0;
    while(token != NULL)
    {
        strcpy(arg[pt],token);
        token = strtok(NULL,delimeters);
        pt++;
    }

    strcpy(arg[pt],"");

    if(pt != 3)
    {
        invalid();
        return;
    }
    if(strcmp(arg[2],"interrupt") && strcmp(arg[2],"newborn"))
    {
        invalid();
        return;
    }

    pid_t pid;
    pid = fork();

    if(pid == 0)
    {
        if(!strcmp(arg[2],"interrupt"))
        {
            interrupt(arg[1]);
        }
        else if(!strcmp(arg[2],"newborn"))
        {
            newborn(arg[1]);
        }
        exit(0);
    }

    if(pid > 0)
    {
        char c;
        while((c = getc(stdin)) != 'q')
        {};

        kill(pid,SIGKILL);
        waitpid(pid,NULL,WUNTRACED);
        return ;
    }
}