#include "headers.h"


void execute(char *command)
{
    char temp[1024] = "";
    strcpy(temp,command);
    
    int f = 0;
    for(int i=0;i<strlen(command);i++)
    {
        if(command[i] == '&')f = 1;
        if(command[i] == '>')f = 2;
        if(command[i] == '<')f = 2;
    }   

    if(f == 1) 
    {
        get_command(command);
        fflush(stdout);
        return ;
    }

    if(f == 2)
    {
        redirect(command);
        return;
    }

    char *token;

    token = strtok(command," \n\t\r");

    if(token == NULL)return;

    if(!strcmp(token,"cd"))
    {
        token = strtok(NULL,"");
        
        cd(token);
    }
    else if(!strcmp(token,"echo"))
    {
        token = strtok(NULL,"");
        echo(token);
    }
    else if(!strcmp(token,"pwd"))
    {
        pwd();
    }
    else if(!strcmp(token,"ls"))
    {
       
        token = strtok(NULL,"");
       
        ls(token);
    }
    else if(!strcmp(token,"pinfo"))
    {
        if(token != NULL)
        {
            token = strtok(NULL,"\t\n ");
        }
        pinfo(token);
    }
    else if(!strcmp(token,"history"))
    {
        if(token != NULL)
        {
            token = strtok(NULL,"\t\n ");
        }
        history(token);
    }
    else if(!strcmp(token,"nightswatch"))
    {
        if(token != NULL)
        {
            token = strtok(NULL,"");
        }

        nightswatch(token);
    }
    else if(!strcmp(token,"setenv"))
    {
        if(token != NULL)
        {
            token = strtok(NULL,"");
        }

        set_env(token);

    }
    else if(!strcmp(token,"unsetenv"))
    {
        if(token != NULL)
        {
            token = strtok(NULL,"");
        }
        unset_env(token);
    }
    else if(!strcmp(token,"jobs"))
    {
        jobs();
    }
    else if(!strcmp(token,"kjob"))
    {
        if(token != NULL)
        {
            token = strtok(NULL,"");
        }
        kjob(token);
    }
    else if(!strcmp(token,"overkill"))
    {
        overkill();
    }
    else if(!strcmp(token,"quit"))
    {
        overkill();
        exit(0);
    }
    else
    {
        get_command(temp);   
    }
    
    fflush(stdout);
       
}