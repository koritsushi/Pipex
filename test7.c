#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) 
{
    int fd1[2], fd2[2];  /* file descriptors 1 & 2 */
	int pid;
	int	infile;
	int	outfile;
	int	i;
	int index;

    if (pipe (fd1) < 0 || pipe (fd2) < 0) { /* open both pipes */
        fprintf (stderr, "pipe creation failed\n");
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

    	if (pid == 0) {
			 /* first child */ 
        	if (i == 0) {
				char	*arg1[] = {"wc", NULL};
				 /* dup write-end of 1st */
				close(fd1[0]);
				dup2(infile, STDIN_FILENO);
				dup2(fd1[1], STDOUT_FILENO); 
				close(fd1[1]);
				close (fd2[0]);
        		close (fd2[1]);
				close(infile);

        		fprintf (stderr, "Exec 1 executing now\n");
        		if (execve("/usr/bin/wc", arg1, NULL) == -1)
        			fprintf (stderr, "Exec 1 failed\n");
				exit(1);
    		} else {
				char	*arg2[] = {"ls", NULL};
				close(fd1[1]);
				dup2(fd1[0], STDIN_FILENO);    /* dup read-end of 1st  */
        		dup2(outfile, STDOUT_FILENO);   /* dup write-end of 2nd */
        		close(fd1[0]);
				close (fd2[0]);
        		close (fd2[1]);
				close(outfile);

        		fprintf (stderr, "Exec 2 executing now\n");
        		if (execve ("/bin/ls", arg2, NULL) == -1)
        			fprintf (stderr, "Exec 2 failed\n");
				exit(1);
			}
			exit(1);
		}
		i++;
	}
	close(infile);
	close(outfile);
	close (fd1[0]);
	close (fd1[1]);
	close (fd2[0]);
	close (fd2[1]);
	int	status = 0;
	while(wait(&status) > 0)
		printf("child process finished\n");

    printf ("done\n");

    return 0;
}
