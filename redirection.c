#include "headers.h"

void redirect(char *string)
{
    char com[256] = "";
    strcpy(com,string);


    char *arg[50];
    char *token;
    token = strtok(string," \t\n");
    
    

    int p = 0;
    while(token != NULL)
    {
        arg[p] = token;
        token = strtok(NULL, " \t\n");
        p++;
    }
    arg[p] = NULL;
    
    char in[50];
    char out[50];

    strcpy(in,"");strcpy(out,"");

    int f;
    int type = -1;


    for(int i=0;i<50;i++)
    {
        if(arg[i] == NULL)break;
        if(!strcmp(arg[i],"<"))
        {
            if(arg[i+1] == NULL)
            {
                printf("Input File Not given\n");
                return;
            }
            
            f = open(arg[i+1],O_RDONLY);
            if(f < 0)
            {
                printf("supunde : %s : No such File or Directory\n",arg[i+1]);
                return;
            }
            close(f);
            strcpy(in,arg[i+1]);
            i++;
        }
        else if(!strcmp(arg[i],">"))
        {
            if(arg[i+1] == NULL)
            {
                printf("Output File Not given\n");
                return;
            }

            f = open(arg[i+1], O_RDONLY | O_CREAT | O_TRUNC, 0644);
            close(f);
            strcpy(out,arg[i+1]);
            i++;
            type = 0;
        }
        else if(!strcmp(arg[i],">>"))
        {
            if(arg[i+1] == NULL)
            {
                printf("Output File Not given\n");
                return;
            }

            f = open(arg[i+1], O_RDONLY | O_CREAT , 0644);
            close(f);
            strcpy(out,arg[i+1]);
            i++;
            type = 1;
        }
    }

    f = 0;
  /*  
    for(int i=0;i<50;i++)
    {
        if(!strcmp(arg[i],"<"))f = 1;
        if(!strcmp(arg[i],">"))f = 1;
        if(!strcmp(arg[i],">>"))f = 1;
        if(f)
        {
            break;
        }
    }
*/
    for(int i=0;i<strlen(com);i++)
    {
        
        if(com[i] == '<')f = 1;
        if(com[i]== '>')f = 1;
        if(f){com[i]='\0';break;}
    }
    
    //printf("%s",com);

    pid_t pid;
    pid = fork();
      

    if(pid < 0)
    {
        perror("Error in forking");
        return;
    }

    if(pid == 0)
    {
        int f1;
        f1 = open(in,O_RDONLY);
        dup2(f1,0);

        int f2;
        if(type == 0)
        {
            f2 = open(out,O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(f2,1);
        }

        if(type == 1)
        {
            f2 = open(out,O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(f2,1);
        }

        execute(com);
        exit(0);
        
    }

    if(pid > 0)
    {
        waitpid(pid,NULL,WUNTRACED);
    }

}