#include "headers.h"

void signal_handler(int n)
{

    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        for (int i = 0; i < 1024; i++)
        {

            if (bg_process[i].pid == pid)
            {

                int exit = WIFEXITED(status);
                char buff[2000] = "";

                if (exit && !(WEXITSTATUS(status)))
                {
                    sprintf(buff, "%s with pid %d exited normally\n", bg_process[i].p_name, pid);
                    write(2, buff, sizeof(buff));
                }
                else
                {
                    sprintf(buff, "%s with pid %d exited abnormaly\n", bg_process[i].p_name, pid);
                    write(2, buff, sizeof(buff));
                }

                process_cnt--;
                strcpy(bg_process[i].p_name, "");
                bg_process[i].pid = -1;
                break;
            }
        }
    }
}