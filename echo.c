#include "headers.h"

void echo(char *string)
{
    
    char *token;

    char delimeters[] = "\t\n\r '";

    token = strtok(string,delimeters);
    

    while(token != NULL)
    {
        printf("%s ",token);
        token = strtok(NULL,delimeters);
    }
    printf("\n");

}