#include "headers.h"

void get_state(char *pid)
{
    char stats[50] = "";
    strcpy(stats,"/proc/");
    strcat(stats,pid);
    strcat(stats,"/stat");

    FILE *f;
    f = fopen(stats,"r");

    char buffer[1024] = "";
    fread(buffer,sizeof(char),sizeof(buffer),f);

    char *token;
    token = strtok(buffer," \t\n");

    int cnt = 1;
    while(token != NULL)
    {
        token = strtok(NULL," \t\n");
        cnt++;
        if(cnt == 3)
        {
            if(!strcmp(token,"T"))
            {
                printf("Stopped ");
                return;
            }
            else
            {
                printf("Running ");
                return;
            }
        }
    }
}

void jobs()
{
    int counter = 1;
    for(int i=0;i<1024;i++)
    {
        if(bg_process[i].pid != -1)
        {
            printf("[%d] ",counter);
            char pid[10] = "";
            sprintf(pid,"%d",bg_process[i].pid);
            get_state(pid);

            printf("%s [%d]\n",bg_process[i].p_name,bg_process[i].pid);
            counter++;
        }
    }   
    
}
