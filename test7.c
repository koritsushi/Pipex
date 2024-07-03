#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (void) {

    int fd1[2], fd2[2];  /* file descriptors 1 & 2 */
    int	fd[2][2];
	int pid;
	int	infile;
	int	outfile;
	int	i;
	int index;

    if (pipe (fd1) < 0 || pipe (fd2) < 0) { /* open both pipes */
        fprintf (stderr, "pipe creation failed\n");
    }
	index = 0;
	while (pipe(fd[index]) < 0 && index < 2)
	{
		index++;
		printf("%d\n", index);
	}
	infile = open("exec.c", O_RDONLY, 0777);
	outfile = open("out", O_RDWR | O_CREAT | O_TRUNC, 0777);
	i = 0;
	while (i < 2)
	{
    	if ((pid = fork ()) == -1) {
        	fprintf (stderr, "fork 1 failed\n");
        	exit (1);
    	}

    	if (pid == 0) {                     /* first child */
        	if (i == 0) {
				dup2 (infile, STDIN_FILENO);
				dup2 (fd1[1], STDOUT_FILENO);   /* dup write-end of 1st */
        		close(infile);
				close (fd1[0]);                 /* close all others */
        		close (fd2[0]);
        		close (fd2[1]);

        		fprintf (stderr, "Exec 1 executing now\n");
        		execlp ("ls", "ls -la", NULL);
        		fprintf (stderr, "Exec 1 failed\n");
    		} else {
				dup2 (fd1[0], STDIN_FILENO);    /* dup read-end of 1st  */
        		dup2 (outfile, STDOUT_FILENO);   /* dup write-end of 2nd */
        		close (outfile);
				close (fd1[1]);                 /* close all others */
        		close (fd2[0]);

        		fprintf (stderr, "Exec 2 executing now\n");
        		execlp ("ls", "ls", NULL);
        		fprintf (stderr, "Exec 2 failed\n");

			}
		}
    	else 
		{
        	int returnStatus;
        	waitpid (pid, &returnStatus, 0);
        	fprintf (stderr, "Back to parent\n");
    	}
		i++;
	}
	int status = 0;
	while(wait(&status) > 0)
		printf("child process done");
    close (fd2[0]);
    close (fd2[1]);
    close (fd1[0]);
    close (fd1[1]);

    printf ("done");

    return 0;
}
