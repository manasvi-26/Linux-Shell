#include "headers.h"
int hist_cnt;

void size_hist()
{
    fp = fopen(history_path, "a+");

    char buf[200];
    hist_cnt = 0;
    while(!feof(fp))
    {
        fgets(buf,sizeof(buf),fp);
        hist_cnt++;
    }
    fclose(fp);    
}

void load_history(char *command)
{
    size_hist();

    if (hist_cnt <= 20)
    {
        fp = fopen(history_path, "a+");

        fputs(command, fp);
        fclose(fp);
    }
    else
    {
        
        fp = fopen(history_path, "r");
        FILE *fp2;

        char temp[1024] = "";
        strcpy(temp, home);
        strcat(temp, "/temp.txt");
        fp2 = fopen(temp, "a+");

        char buffer[1024];
        int cnt = 0;
        while (!feof(fp))
        {
            strcpy(buffer, "");
            fgets(buffer, sizeof(buffer), fp);

            if (!feof(fp))
            {
                cnt++;
                if (cnt != 1)
                {
                    fprintf(fp2, "%s", buffer);
                }
            }
        }

        fprintf(fp2, "%s", command);
        fclose(fp);
        fclose(fp2);

        remove(history_path);
        rename(temp, history_path);
        return;
    }
}


void history(char *string)
{
    int n = 10;
    if(string != NULL)
    {
        n = atoi(string);
    }

    if(n > 20)n = 10;

    size_hist();


    char hist[hist_cnt][200];
    fp = fopen(history_path,"r");
    
    char buffer[200];

    int pt = 0;
    strcpy(hist[pt],"");
    while(!feof(fp))
    {
        strcpy(hist[pt],"");
        fgets(hist[pt],sizeof(hist[pt]),fp);
        pt++;
    }
    
    int val = 0;
    if((hist_cnt - n -1) > val)val = hist_cnt - n - 1;

    for(int i=val;i< pt -1;i++)
    {
        printf("%s",hist[i]);
    }

}
