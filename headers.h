#ifndef HEADERS_H
#define HEADERS_H


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h> 
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/dir.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>


char home[1024];
char user[1024];
char syst[1024];
char currDir[1024];


void cd(char *Args);
void pwd();
void echo(char *string);
void execute(char *command);
void ls(char *string);
void pinfo(char *string);

void get_command(char* string);

void print_prompt();
void GetDir(char* dir);
void load_history(char*command);
void history(char * string);
void nightswatch(char *arg);

void signal_handler(int n);
void Check(int pid);

void redirect(char *string);
void set_env(char *string);
void unset_env(char *string);
void jobs();
void kjob(char *string);
void overkill();

void get_job(char*string,int type);

void fg(int job_number,int pid, char *name);
void bg(int job_number,int pid, char *name);

void piping(char *string);


//for process:
struct proc
{
    char p_name[1024];
    int pid;
};

int job;

struct proc ForeProc;

struct proc bg_process[1024];


int process_cnt;

//for history:
char history_path[1024];
char last_command[1024];
int Shell;
FILE * fp;


//for colors:
#define reset() printf("\033[0m"); 
#define clear() printf("\033[H\033[J");


#define RED printf("\033[1;31m");
#define Green printf("\033[1;32m");

#define Cyan printf("\033[1;36m"); 
#define Yellow printf("\033[1;33m"); 
#define Magenta printf("\033[1;35m"); 
#define Blue printf("\033[1;34m"); 

#endif