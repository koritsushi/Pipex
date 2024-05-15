#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char* argv[])
{
	int fd[2];
	int pid1;
	int pid2;
	
	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0) {
		// first child (ping)
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		// get access to the path environment variable
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	// else is not necessary. after here, code only executed by the parent
	// duplicate fd, both pointing to the same pipe
	pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0) {
		// child process 2 (grep)
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "round-trip", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
