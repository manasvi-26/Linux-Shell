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
        face = 0;
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
            face = 0;
            perror("Error");
            return;
        }

        getcwd(last_workingDirectory,sizeof(last_workingDirectory));
        GetDir(last_workingDirectory);

    }
    else if(token[0] == '-' && token[1] == '\0')
    {
        printf("%s\n",last_workingDirectory);
    }
    else
    {   
        if(chdir(token) == -1)
        {
            face = 0;
            perror("Error");
            return;
        }

        getcwd(last_workingDirectory,sizeof(last_workingDirectory));
        GetDir(last_workingDirectory);
    }    
}
