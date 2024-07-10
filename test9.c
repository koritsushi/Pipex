#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char **envp) 
{
    int fd[2][2];  /* file descriptors for 2 pipes */
    int pid;
    int infile;
    int outfile;
    int i;
    int max = 3;

    infile = open("exec.c", O_RDONLY, 0777);
    outfile = open("out", O_RDWR | O_CREAT | O_TRUNC, 0777);

    // Create only 2 pipes for 3 processes
    for (i = 0; i < max - 1; i++) {
        if (pipe(fd[i]) == -1) {
            fprintf(stderr, "pipe creation failed\n");
            exit(1);
        }
    }

    for (i = 0; i < max; i++)
    {
        if ((pid = fork()) == -1) {
            fprintf(stderr, "fork %d failed\n", i);
            exit(1);
        }

        if (pid == 0) {
            // Child process
            if (i == 0) {
                // First child (ls)
                char *arg1[] = {"ls", NULL};
                close(fd[i][0]);  // Close read end of first pipe
                dup2(infile, STDIN_FILENO);
                dup2(fd[i][1], STDOUT_FILENO);
                close(fd[i][1]);
                close(infile);
                close(fd[i + 1][0]);
                close(fd[i + 1][1]);

                fprintf(stderr, "Exec 1 (ls) executing now\n");
                if (execve("/bin/ls", arg1, envp) == -1)
                    fprintf(stderr, "Exec 1 (ls) failed\n");
            } else if (i == max - 1) {
                // Third child (wc)
                char *arg3[] = {"wc", NULL};
                close(fd[0][0]);
                close(fd[0][1]);
                close(fd[i - 1][1]);  // Close write end of second pipe
                dup2(fd[i - 1][0], STDIN_FILENO);
                dup2(outfile, STDOUT_FILENO);
                close(fd[i - 1][0]);
                close(outfile);

                fprintf(stderr, "Exec 3 (wc) executing now\n");
                if (execve("/usr/bin/wc", arg3, envp) == -1)
                    fprintf(stderr, "Exec 3 (wc) failed\n");
            } else {
				// Second child (cat)
                char *arg2[] = {"cat", NULL};
                close(fd[i - 1][1]);  // Close write end of first pipe
                close(fd[i][0]);  // Close read end of second pipe
                dup2(fd[i - 1][0], STDIN_FILENO);
                dup2(fd[i][1], STDOUT_FILENO);
                close(fd[i - 1][0]);
                close(fd[i][1]);

                fprintf(stderr, "Exec 2 (cat) executing now\n");
                if (execve("/bin/cat", arg2, envp) == -1)
                    fprintf(stderr, "Exec 2 (cat) failed\n");
            }
            exit(1);
        } else {
            // Parent process
            // Close unused pipe ends in the parent immediately after forking
            if (i == 0) {
                close(fd[0][1]);  // Close write end of first pipe
            } else if (i == 1) {
                close(fd[0][0]);  // Close read end of first pipe
                close(fd[1][1]);  // Close write end of second pipe
            }
        }
    }

    close(infile);
    close(outfile);
    close(fd[1][0]);  // Close remaining read end of second pipe

    int status = 0;
    while (wait(&status) > 0)
        printf("Child process finished\n");

    printf("Done\n");

    return 0;
}