#include "headers.h"

int flag_l = 0;
int flag_a = 0; 

void flags(char *s)
{
    
    char*token;
    token = strtok(s," \n\t");
    while(token != NULL)
    {
                
        if(!strcmp(token,"-l"))
        {
            flag_l = 1;
        }
        else if(!strcmp(token,"-a"))
        {
            flag_a = 1;
        }
        else if(!strcmp(token,"-la") || !strcmp(token,"-al"))
        {
            flag_l = 1;
            flag_a = 1;
        }
        token = strtok(NULL," \n\t");
    }

    //printf("Flag l is %d\n",flag_l);
    //printf("Flag a is %d\n",flag_a);
}

void getpath(char* s, char *final_path)
{
    if(s[0] == '~')
    {
        strcpy(final_path,home);
        strcat(final_path,&s[1]);
    }
    else
    {
        strcpy(final_path,s);
    }
}

void ls_print(char *Path)
{
    struct dirent *d;

    DIR *dir;

    dir = opendir(Path);

    if(!dir)
    {
        perror("Cant open Directory");
        return ;
    }

    int items = 0;
    char **item_list;
    item_list  = malloc((1024) * sizeof(char *));
    
    
    while((d = readdir(dir)) != NULL)
    {
        if((d->d_name[0] == '.' &&  flag_a) || (d->d_name[0] != '.'))
        {
            int x = strlen(d->d_name);
            x+=2;
            item_list[items] = malloc(x * sizeof(char)); 
            strcpy(item_list[items],d->d_name);
            items++;
        }
    }

    for(int i=0;i<items;i++)
    {
        if(!flag_l)
        {
            printf("%s\n",item_list[i]);
        }
        else
        {
            //get the file path
            char file[1024] = "";
            strcpy(file,Path);
            strcat(file,"/");
            strcat(file,item_list[i]);

            struct stat filestat;

            if(lstat(file,&filestat) <0)
            {
                perror("Error");
                return ;
            }

            //printing permisions
            printf( (S_ISDIR(filestat.st_mode)) ? "d" : "-");
            printf( (filestat.st_mode & S_IRUSR) ? "r" : "-");
            printf( (filestat.st_mode & S_IWUSR) ? "w" : "-");
            printf( (filestat.st_mode & S_IXUSR) ? "x" : "-");
            printf( (filestat.st_mode & S_IRGRP) ? "r" : "-");
            printf( (filestat.st_mode & S_IWGRP) ? "w" : "-");
            printf( (filestat.st_mode & S_IXGRP) ? "x" : "-");
            printf( (filestat.st_mode & S_IROTH) ? "r" : "-");
            printf( (filestat.st_mode & S_IWOTH) ? "w" : "-");
            printf( (filestat.st_mode & S_IXOTH) ? "x" : "-");


            //printing number of hard links
            printf("\t%ld",filestat.st_nlink);


            //printing user name
            struct passwd *user;
            user = getpwuid(filestat.st_uid);
            
            printf("\t%s",user->pw_name);


            //printing group name
            struct group *grp;
            grp = getgrgid(filestat.st_gid);

            printf("\t%s",grp->gr_name);

            //printing file size
            if(filestat.st_size < 1000000)
            {
                printf("\t%ld",filestat.st_size);
            }
            else
            {
                printf(" %ld",filestat.st_size);
            }
            

            //printing last modified time
            
            
            struct tm *info = localtime( &(filestat.st_mtime));

            char Time[64] = "";
            strftime(Time,sizeof(Time),"%b %d  %H:%M",info);

            printf("\t\t%s",Time);

            //printing name
            printf("\t%s",item_list[i]);

            printf("\n");
        
        }
    }
}

void ls(char *string)
{
    if(string == NULL)
    {
        ls_print(".");
        flag_a = 0;
        flag_l = 0;
        return;
    }
    

    char temp[1024] = "";
    strcpy(temp,string);

    flags(temp);

    int is_dir = 0;

    char*token ;

    token = strtok(string," \t\n");

    while(token != NULL)
    {
        if(token[0] != '-')
        {
            is_dir = 1;
            char final_path[1024] = "";
            getpath(token,final_path);

            Magenta printf("Directory:\n"); reset();
            ls_print(final_path);
        }
        token = strtok(NULL," \t\n");
    }

    if(!is_dir)
    {
        ls_print(".");
    }

    flag_a = 0;
    flag_l = 0;
   
}