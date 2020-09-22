#include "headers.h"

void pwd()
{
    getcwd(currDir,sizeof(currDir));
    printf("%s\n",currDir);
}