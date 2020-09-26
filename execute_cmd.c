#include "headers.h"

int check_piping(char *command)
{
    int f = 0;
    for(int i=0;i<strlen(command);i++)
    {
        if(command[i] == '|')f = 1;
    }
    return f;
}

int check_redirection(char* command)
{
    
    int f = 0;
    for(int i=0;i<strlen(command);i++)
    {
        if(command[i] == '>')f = 1;
        if(command[i] == '<')f = 1;
    } 
    return f;
}

void execute(char *command)
{
    
    char temp[1024] = "";
    strcpy(temp,command);

    int f = 0;

    if(check_piping(command))
    {
        piping(command);
        return;
    }
    
    if(check_redirection(command))
    {
        redirect(command);
        return;
    }

    for(int i=0;i<strlen(command);i++)
    {
        if(command[i] == '&')f = 1;
    }   

    if(f == 1) 
    {
        get_command(command);
        fflush(stdout);
        return ;
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
    else if(!strcmp(token,"fg"))
    {
        if(token != NULL)
        {
            token = strtok(NULL,"");
        }
        get_job(token,1);
    }
    else if(!strcmp(token,"bg"))
    {
        if(token != NULL)
        {
            token = strtok(NULL,"");
        }
        get_job(token,0);
    }
    else
    {
        get_command(temp);   
    }
    
    fflush(stdout);
       
}