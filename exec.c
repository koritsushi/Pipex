#include <unistd.h>
#include <stdio.h>
#include "./libft/libft.h"

int	ft_find_path(char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
	{
		if (envp[i][j] != '\0')
		{
			if (ft_strncmp("PATH=", envp[i], 5) == 0)
					return (i);
			i++;
		}
	}
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*command[] = {"/bin/grep", NULL};
	char	*bin_file = command[0];
	int		i;

	if (execve(bin_file, command, NULL) == -1)
	{
		fprintf(stderr, "Error executing %s\n", bin_file);
	}
	i = ft_find_path(envp);
	printf("%d\n", ft_find_path(envp));
	printf("%s\n", envp[i]);
	printf("done!\n");
	return (0);
}
