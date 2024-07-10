#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


void	ft_parent_process(int fd[2][2], int i, int max, int infile, int outfile)
{
	if (i == 0) {
		close(fd[i][1]); 
		close(infile);
	} else if (i == max - 1) {                
		close(infile);
		close(outfile);
		close(fd[i - 1][1]);  // Close remaining read end of second pipe
	} else {
		close(fd[i - 1][0]);  // Close read end of first pipe
		close(fd[i][1]);  // Close write end of second pipe
	}
}

void	ft_child_process(int fd[2][2], char **envp, int i, int max, int infile, int outfile)
{
	if (i == 0) 
	{
		char	*arg1[] = {"ls", NULL};
			/* dup write-end of 1st */
		close(fd[i][0]);
		dup2(infile, STDIN_FILENO);
		dup2(fd[i][1], STDOUT_FILENO); 
		close(fd[i][1]);
		close(infile);

		fprintf (stderr, "Exec 1 executing now\n");
		if (execve("/bin/ls", arg1, envp) == -1)
			fprintf (stderr, "Exec 1 failed\n");
	} else if (i == max - 1) {
		char	*arg3[] = {"cat", NULL};
		close(fd[i - 1][1]);
		dup2(fd[i - 1][0], STDIN_FILENO);    /* dup read-end of 1st  */
		dup2(outfile, STDOUT_FILENO);   /* dup write-end of 2nd */
		close(fd[i - 1][0]);
		close(outfile);

		fprintf (stderr, "Exec 2 executing now\n");
		if (execve ("/bin/cat", arg3, envp) == -1)
			fprintf (stderr, "Exec %d failed\n", i);
	} else {
		char	*arg2[] = {"wc", NULL};
		close(fd[i - 1][1]);
		close(fd[i][0]);
		dup2(fd[i - 1][0], STDIN_FILENO);    /* dup read-end of 1st  */
		dup2(fd[i][1], STDOUT_FILENO);   /* dup write-end of 2nd */
		close(fd[i - 1][0]);

		fprintf (stderr, "Exec 3 executing now\n");
		if (execve ("/usr/bin/wc", arg2, envp) == -1)
			fprintf (stderr, "Exec 3 failed\n");
	}
}

int main(int argc, char *argv[], char **envp) 
{
    int fd[2][2];  /* file descriptors 1 & 2 */
	int pid;
	int	infile;
	int	outfile;
	int	i;
	int	max;
	int index;

	infile = open("exec.c", O_RDONLY, 0777);
	outfile = open("out", O_RDWR | O_CREAT | O_TRUNC, 0777);
	i = 0;
	max = 3;
	index = 0;
    while (index < max - 1) { /* piping */
		if (pipe(fd[index]) == -1)
        	(fprintf (stderr, "pipe creation failed\n"), exit(1));
		index++;
    }
	printf("pipe index: %d\n", index);
	while (i < max)
	{
    	if ((pid = fork ()) == -1) {
        	fprintf (stderr, "fork 1 failed\n");
        	exit (1);
    	}

    	if (pid == 0) {
			 /* first child */ 
			ft_child_process(fd, envp, i, max, infile, outfile);
		} else {
			ft_parent_process(fd, i, max, infile, outfile);
		}
		i++;
	}
	
	int	status = 0;
	while(wait(&status) > 0)
		printf("child process finished\n");

    printf ("done\n");

    return 0;
}
