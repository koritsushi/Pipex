#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // Child process
        close(pipefd[1]); // Close the write end of the pipe

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, BUFFER_SIZE)) > 0) {
            fwrite(buffer, 1, bytes_read, stdout);
        }

        close(pipefd[0]); // Close the read end of the pipe
        return 0;
    } else { // Parent process
        close(pipefd[0]); // Close the read end of the pipe

        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            perror("open");
            return 1;
        }

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
            if (write(pipefd[1], buffer, bytes_read) != bytes_read) {
                perror("write");
                close(fd);
                return 1;
            }
        }

        close(fd);
        close(pipefd[1]); // Close the write end of the pipe
        waitpid(pid, NULL, 0); // Wait for the child process to finish
        return 0;
    }
}