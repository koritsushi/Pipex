# Pipex
a project dive in multiprocess programming in executing command from shell and piping input and output from parent to child, child to child process.

each program has 
- standard input	0 (stdin)
- standard output	1 (stdout)
- standard error	2 (stderr)

every pipe when dup2 the program input or output must close either one end on each side. be it parent to process, process to parent or process to prcocess.

so by using dup2 function to redirect the program stdout to pipe[1], pipe[0] must be close to send a EOF(end of file signal) to prevent a pipe hang or program freeze. this can be apply to other way such as redirect pipe[0] to the program stdin.

similarly like how you manipulate write() function with the first parameter to be able to print out to standard input, standard output and standard error.

why do we need to redirect it?
we redirect it to simulate the pipe function on linux/unix shell '|' between command such as "ls | wc".

and to run each of this command, you will require to get the environment path.

in the int main(int argc, char **argv) command line argument you can add anotherchar **variable to get the environment path. which will require you to search and join up both environment path and command input by the user.

how to know if the command is valid or invalid to execute?
by using int access() function to check if its exist.
if not it will return -1.