#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	main()
{
	int		id1 = fork();
	int		id2 = fork();

	while (wait(NULL) != -1 || errno != ECHILD)
	{
		;
	}
	if (id1 == 0)
	{
		if (id2 == 0)
		{
			printf("grandchild\n");
		}
		else
		{
			printf("1st child of parent\n");
		}
	}
	else
	{
		if (id2 == 0)
		{
			printf("2nd child of parent\n");
		}
		else
		{
			printf("parent\n");
		}
	}
	return (0);
}
