# Description
### To run the shell, run the command `make` on the terminal. This creates an executable `a.out` which can be run by `./a.out`

# Assumptions
## As stated/approved in the doubt document:
### For peek and seek, green has been used for executables, white for files and blue for directories
### "Lexicographical ordering implies sorting a set of strings based on the ASCII values of the individual characters in a string". README.md appears before headers.h for peek
### For peek -l, the output is displayed exactly like bash, `%h %d %H:%M` for files not as old as 6 months, and `%h %d %Y` for files older than that. An average month length of 30.4 days has been considered to calculate this.
### <background_process_pid> is printed whenever one is executed as shown in Specification 6
### If background process is of a valid command with invalid operands, the pid will be printed and appropriate messages displayed. On entering the next prompt, the process will be displayed to have exited normally.
### pastevents are displayed in a specific format of `<command> ; <command> & command>` or if the last command is a background process, `<command> ; <command> & command> &`.
### For seek, when tthe arget is a file, all files with the filename of the form `file`, `file.extension` are displayed
### Commands followed by erronous commands separated by `;` or `&` are executed
### When a prompt takes >2 seconds to execute, 
