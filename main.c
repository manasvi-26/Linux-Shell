#include "headers.h"

static int nread = -1;

void init()
{
    clear();
    printf("\n\n\n");
    
    Magenta
    printf("\t\t\t*** Welcome to Shell Supunde ***");
    printf("\n\n\n");
    reset();

    memset(user, '\0', sizeof(user));
    memset(syst, '\0', sizeof(syst));
    memset(home, '\0', sizeof(home));
    memset(currDir, '\0', sizeof(currDir));

    for(int i=0;i<1024;i++)
    {
        strcpy(bg_process[i].p_name ,"");
        bg_process[i].pid = -1;
    }
    process_cnt = 1;
    job = 0;

    fflush(stdout);

    
}

void GetDir(char* dir)
{
    getcwd(currDir,sizeof(currDir));
   
    int flag = 0;
    for(int i=0;i<strlen(home);i++)
    {
        if(home[i] != currDir[i])
        {
            flag = 1;
        }
    }


    if(flag)
    {
        strcpy(dir,"");
        strcpy(dir,currDir);
    }
    else
    {
        dir[0] = '~';
        int pt = 1;
        for(int i=strlen(home);i<strlen(currDir);i++)
        {
            dir[pt] = currDir[i];
            pt++;
        }
        dir[pt] = '\0';        
    }
    return;
}

void print_prompt()
{
    RED printf("<"); reset()
    Cyan  printf("%s@%s:",user,syst); reset()
    char dir[1024] = "";
    GetDir(dir);
    
    Yellow printf("%s",dir); reset();
    RED printf(">"); reset();
}



char *get_input()
{
    size_t inp_sz = 0;
    char *input_line = NULL;
    nread = (getline(&input_line, &inp_sz, stdin));

    return input_line;

}

int Commands(char *Input)
{
    int cnt = 0;
    for(int i=0;i<strlen(Input);i++)
    {
        if(Input[i] == ';')cnt++;
    }    
    return cnt;
}


void append(char *string)
{
    if(strcmp(last_command,string) && strcmp(string,"\n"))
    {
        strcpy(last_command,string);
        load_history(last_command);
    }
}

//void ctrl_c_handler(int sig_num) 
//{ 
//    
//	return;
//}


int main()
{
    init();
       
    getlogin_r(user,sizeof(user));
    gethostname(syst,sizeof(syst));
    getcwd(home,sizeof(home));

    strcpy(history_path,home);
    strcat(history_path,"/history.txt"); 
    strcpy(last_command,"");
    

    signal(SIGCHLD,signal_handler); 
    //signal(SIGINT, ctrl_c_handler);

    while(1)
    {
        print_prompt();
        
        char *input;
    
        input = get_input();
        if(nread == -1)
        {
            overkill();
            exit(0);
        }

        
        char history_input[1024] = "";
        strcpy(history_input,input);

        int total = Commands(input);
        total += 5;
      
        char *token;
        
        token = strtok(input,";");
       

        char command_list[total][1024];

        
        int pt = 0;
        int cnt = 0;
        while(token != NULL)
        {   
            cnt++;
            int x = strlen(token);
            x+=2;
            
            strcpy(command_list[pt],token);
            token = strtok(NULL,";");
            pt++;
        }

        strcpy(command_list[pt],"");


        for(int i=0;i<cnt;i++)
        {
            if(strcmp(command_list[i],""))
            {
                execute(command_list[i]);
            }
        }

        append(history_input);
    }

}