#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int n, pipefd[2];
    char buf[1025], *data = "hello... this is sample data";

    pipe(pipefd);
    write(pipefd[1], data, strlen(data));
    if ((n = read(pipefd[0], buf, 1024)) >= 0)
    {
        buf[n] = 0; /* terminate the string */
        printf("read from the pipe: \"%s\"\n", buf);
    }
    return 0;
}