# Description
### To run the shell, run the command `make` on the terminal. This creates an executable `a.out` which can be run by `./a.out`
`.
├── a.out
├── background.c
├── background.h
├── commands.c
├── commands.h
├── headers.h
├── history
├── main.c
├── makefile
├── myString.c
├── myString.h
├── pastevents.c
├── pastevents.h
├── peek.c
├── peek.h
├── proclore.c
├── proclore.h
├── prompt.c
├── prompt.h
├── README.md
├── seek.c
├── seek.h
├── syscomm.c
├── syscomm.h
├── warp.c
└── warp.h
`
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

