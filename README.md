# SUPUNDE - Linux Shell in C

##  Directions to Run the shell:
1.  Run the command 'make'
2.  Run './supunde' to get a prompt
3.  Exit by hitting Ctrl D or 'quit'

##   Built in Commands:

### 1.   ls [-l -a -la -al] Directory

        Implemented in 'ls.c' file

    - 'ls' lists all the files and directories 
    - 'ls -l' long list
    - 'ls -a' diplays hidden files as well
    - 'ls -la' and 'ls -al' implemented
    - Multiple directories can be given as an argument
    - The order of the flags and directories can be arbitrary

### 2.   cd [directory]
    
        Implemented in 'cd.c' file

    - Changes directory to the directory specified.
    - Throws an error if the directory does not exist or if multiple arguments have been passed
    - cd '-' : switched and prints the last working directory. 

### 3.   pwd
    
        Implemented in 'pwd.c' file

    - Displays path of the current working directory.

### 4.   echo [argument]

        Implemented in 'echo.c' file

    - displays argument in stdout
    - Note : the following have not been handled :  ('', "" , \t )

### 5.   pinfo [pid]

        Implemented in 'pinfo.c' file

    - Display Information related to the process with the give pid.
    - If no pid mentioned displays for the current running process(supunde).
    - Information displayed : pid , Process status, Memory , Exectuable Path of the process.

### 6.   history [number]

        Implemnted in 'history.c' file

    - displays the last 'number' of commands 
    - Max limit is 20
    - if no number specified prints the last 10

### 7.   nightswatch -n [seconds] [command]

        Implemented in 'nightswatch.c' file

    - Executes every n seconds and prints in every new line.
    - Commands used : 'interrupt' and 'newborn'
    - interrupt : prints the number of times cpu has been interrupted by the keyboard.
    - newborn : prints the pid of the most recent process created on the system.
    - To exit the process hit 'q' + enter.

### 8.   setenv var [value]

        Implemented in 'env_variable.c' file

    - Sets value of environment variable 'var' to 'value'
    - if no value given sets it to null string

### 9.   unsetenv [var]

        Implemented in 'env_variable.c' file
    
    - Deletes environment variable 'var' 

### 10.  fg [number]
        
        Implemented in 'fgbg.c'

    - Brings running or stopped background process to the foreground

### 11.  bg [number]

        Implemented in 'fgbg.c'

    - Changes a stopped background job to a running background job

### 12.  overkill

        Implemented in 'overkill.c'
    
    - kills all background processes

### 13. jobs

        Implemented in 'jobs.c'
    
    -  Prints all background processes
    -  Format : [job number] pid  process_state process_name
    -  Process_state is either 'running' or 'stopped'


### 14. kjob [jobnumber] [signal number]

        Implemented in 'kjob.c'

    -  sends given signal to the process with given pid


##  Foreground and Background Processes :

        Implemented in 'process.c' file

    1)  Foreground : Processes that require the terminal to halt until their completion.
                        example : vi,emacs
    2)  Background : Processes that run simultaneuosly without interrupting the terminal.
                    Implemented using command followed by '&'.
                    Current background process number with its pid and name is printed on start.
                     On termination prints the pid, name and exit status of the process.
                    example : emacs &, vi &

## Signal Handling :

    1)  Ctrl+C  : Sends SIGINT signal to all processes in the foreground process group. All
                  processes forked from the shell gets interrupted. 

    2)  Ctrl+Z  : Suspends currently running foreground process.State changes from 'running'
                  to 'stopped'.
                  
## Note :

        - Every command has been implemented in their respective .c file.
        - Process starts at 'main.c' file
        - 'Signal.c' file contains the signal handler function(called by SIGCHLD).
        - 'history.txt' file contains the last 20 (at max) commands entered.
        - 'headers.h' file contains definitions of all the functions and global variables used.
        -  Information about the previous command's exit code has been displayed next to
           next prompt as ​ :')​ if the command exited successfully, or as ​:'(​ if
           it encountered an error.
       
