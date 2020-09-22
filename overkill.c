#include "headers.h"

void overkill()
{
    for(int i=0;i<1024;i++)
    {
        if(bg_process[i].pid != -1)
        {
            kill(bg_process[i].pid,9);
            bg_process[i].pid = -1;
            process_cnt--;
        }
    }
    job = 0;
}