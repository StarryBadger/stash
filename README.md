[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/76mHqLr5)
# Description


## Final branch
### To run the shell, run the command `make` on the terminal. This creates an executable `a.out` which can be run by `./a.out`

.
├── activities.c (implementation of activities function) 
├── activities.h (header files of activities.c) 
├── a.out (executable) 
├── background.c (implements background process list) 
├── background.h (header files of background.c) 
├── commands.c (executes commands entered in the prompt by the user) 
├── commands.h (header files of commands.c) 
├── fgbg.c (implemented fg and bg commands)
├── fgbg.h (header files of fgbg.c)  
├── headers.h (common header file with libraries and global variables) 
├── history (file to store last 15 commands for pastevents) 
├── iMan.c  (implemented iMan)
├── iMan.h (header files of iMan.c) 
├── main.c  (displays prompt and reads input and executes command)
├── makefile  (makes file a.out)
├── myString.c  (my implementation of string)
├── myString.h (header files of myString.c) 
├── neonate.c  (implemented neonate)
├── neonate.h (header files of neonate.c) 
├── pastevents.c  (implemented pastevents)
├── pastevents.h (header files of pastevents.c) 
├── peek.c  (implemented peek)
├── peek.h (header files of peek.c) 
├── ping.c  (implemented ping)
├── ping.h (header files of ping.c) 
├── proclore.c  (implemented proclore)
├── proclore.h (header files of proclore.c) 
├── prompt.c  (displays prompt)
├── prompt.h (header files of prompt.c) 
├── raw.c  (enables and disables raw mode)
├── raw.h (header files of raw.c) 
├── README.md  (current file)
├── redirection.c  (implemented piping and I/O redirection)
├── redirection.h (header files of redirection.c) 
├── seek.c  (implemented seek)
├── seek.h (header files of seek.c) 
├── signalhandler.c  (implemented signal handlers)
├── signalhandler.h (header files of signalhandler.c) 
├── syscomm.c  (execute system commands using execvp)
├── syscomm.h (header files of syscomm.c) 
├── warp.c  (implemented warp)
└── warp.h (header files of warp.c) 

- background.* handles background processes including functions for the list containing them
- commands.* execute the commands entered in prompt. Also responsble for parsing
- header.h contains common header files
- history file to store history for pastevents
- main.c takes input 
- myString.* contains string functions
- pastevents.* displays, deletes and executes pastevents
- peek.* works like ls
- proclore.* displays process details
- prompt.* displays prompt to user
- seek.* finds for a file or directory in he given directory
- syscomm.* handles system commands
- warp.* works like cd

# Assumptions
## As stated/approved in the doubt document:
- `bash` has been used as the default hsell to determine outputs
- For peek and seek, green has been used for executables, white for files and blue for directories
- "Lexicographical ordering implies sorting a set of strings based on the ASCII values of the individual characters in a string". README.md appears before headers.h for peek
- For peek -l, the output is displayed exactly like bash, `%h %d %H:%M` for files not as old as 6 months, and `%h %d %Y` for files older than that. An average month length of 30.4 days has been considered to calculate this.
- <background_process_pid> is printed whenever one is executed as shown in Specification 6
- If background process is of a valid command with invalid operands, the pid will be printed and appropriate messages displayed. On entering the next prompt, the process will be displayed to have exited normally.
- pastevents are displayed in a specific format of `<command> ; <command> & command>` or if the last command is a background process, `<command> ; <command> & command> &`.
- For seek, when tthe arget is a file, all files with the filename of the form `file`, `file.extension` are displayed
- Commands followed by erronous commands separated by `;` or `&` are executed
- When a prompt takes >2 seconds to execute, the name of the first command is displayed (as we were allowed to display anything with proper assumptions and this felt the most aethetically pleasing)
- error messages due to functions defined in C, like, perror messages are not displayed in red.
- Assumptions have been made for path lengths to be PATH_MAX/PATH_MAX-1 as well as that only be 50 commands in one prompt, each with max 128 paramters and each parameter with max 127 characters.
- For activities, 'T' state processes are considered are Stopped, all other processes are considered Running
- A background process brought to foreground is rmoved from the background process list. No output is displayed on its termination.
- Exited background processes are displayed between the two prompts when the ended.
- Stopped processes, on killing the terminal are finished after catching a deadly signal HUP
- iMan determines that the command is invalid if the man page has no instage of `NAME\n`, which is a common observation.
- Signals are implemented for system commands, which are implemented by fork().
