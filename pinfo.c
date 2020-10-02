#include "headers.h"

void pinfo(char * string)
{
    char pid[10] = "";
    //printf("%s\n",string);

    if(string == NULL)
    {
        sprintf(pid,"%d",Shell);
    }
    else
    {
        char *t;
        
        t = strtok(string," \t\n");
        
        strcpy(pid,t);
    }
    
    //file stat path
    char stats[50] = "";
    strcpy(stats,"/proc/");strcat(stats,pid); strcat(stats,"/stat");
    
    FILE *f;
    f = fopen(stats,"r");

    if(!f)  
    {
        face = 0;
        printf("Process with ID %s does not exist\n", pid);
        return ;
    }
    
    char buffer[1024] = "";
    fread(buffer,sizeof(char),sizeof(buffer),f);
    
    
    char *token;
    token = strtok(buffer," \t\n");
    
    
    printf("pid --> %s\n",token);
    int cnt = 1;
    while(token != NULL)
    {
        token = strtok(NULL," \t\n");
        cnt++;
        if(cnt == 3)
        {
            printf("Process Status --> {%s}\n",token);
        }
        if(cnt == 23)
        {
            printf("memory --> %s\t{Virtual Memory}\n",token);
            break;
        }
    }

    //finding executable Path:

    char exec[50] = "";
    strcpy(exec,"/proc/");strcat(exec,pid);strcat(exec,"/exe");
    
    char exec_path[1024] = "";
    int ret = readlink(exec,exec_path,sizeof(exec_path));
    if(ret == -1)
    {
        printf("No path for executable\n");
        return;
    }

    
    GetDir(exec_path);
    printf("Executable Path --> %s\n",exec_path);

}