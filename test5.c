#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int file_fd, pipe_fd[2];
    pid_t pid;
    char buffer[1024];
    ssize_t bytes_read;

    // Open a file
    file_fd = open("example.txt", O_RDONLY);
    if (file_fd == -1) {
        perror("open");
        return 1;
    }

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) { // Child process
        // Redirect the pipe write end to the standard output
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Close the file and pipe
        close(file_fd);
        close(pipe_fd[0]);
        close(pipe_fd[1]);

        // Execute the file
        execlp("cat", "cat", "example.txt", NULL);
        perror("execlp");
        return 1;
    } else { // Parent process
        // Redirect the pipe read end to the standard input
        dup2(pipe_fd[0], STDIN_FILENO);

        // Close the file and pipe
        close(file_fd);
        close(pipe_fd[0]);
        close(pipe_fd[1]);

        // Read from the standard input and print the contents
        while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }

        // Wait for the child process to finish
        waitpid(pid, NULL, 0);
    }

    return 0;
}

