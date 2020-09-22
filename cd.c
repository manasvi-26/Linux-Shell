#include "headers.h"

void cd(char *Args)
{
    char *token;

    const char delimeters[] = "\t\n\r ";
    
    token = strtok(Args, delimeters);
    

    //get number of extra arguments
    int count = 0;
    while (token != NULL)
    {
        token = strtok(NULL, delimeters);
        count++;
    }

    if (count > 1)
    {
        printf("Too many arguments\n");
        return ;
    }


    token = strtok(Args, delimeters);
    if (token == NULL)         
    {
        chdir(home);
        getcwd(currDir,sizeof(currDir));
        return ;
    }
 
    if (token[0] == '~')
    {
        char new[1024] = "";
        
        strcpy(new, home);

        strcat(new,&token[1]);
        if(chdir(new) == -1)
        {
            perror("Error");
        }
    }
    else
    {   
        if(chdir(token) == -1)
        {
            perror("Error");
        }
    }    
}
