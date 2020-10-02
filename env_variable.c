#include "headers.h"

void set_env(char *string)
{
    char*token;
    token = strtok(string," \n\t");

    char *arg[5];
    int p = 0;
    while(token != NULL)
    {
        arg[p] = token;
        token = strtok(NULL," \t\n");
        p++;
    }

    arg[p] = NULL;
    if(p == 1)
    {
        int check = setenv(arg[0],"",1);
        if(check == -1){perror("Error");face = 0;}
    }
    else if(p == 2 )
    {
        int check = setenv(arg[0],arg[1],1);
        if(check == -1){perror("Error");face = 0;}
    }
    else
    {
        face = 0;
        RED printf("Supunde : Invalid Syntax\n");reset();
        Magenta printf("Usage : ");reset();
        printf("setenv var [val]\n");
    }

}

void unset_env(char *string)
{
    char* token;
    token = strtok(string," \t\n");

  
    char *arg[5];
    int p = 0;
    while(token != NULL)
    {
        arg[p] = token;
        token = strtok(NULL," \t\n");
        p++;
    }

    arg[p] = NULL;

    if(p == 1)
    {
        int check = unsetenv(arg[0]);
        if(check == -1){perror("Error");face = 0;}
    }
    else
    {
        face = 0;
        RED printf("Supunde : Invalid Syntax\n");reset();
        Magenta printf("Usage : ");reset();
        printf("unsetenv var\n");        
    }

}