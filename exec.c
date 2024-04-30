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

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*dst;

	i = 0;
	j = 0;
	k = 0;
	if (s1 == NULL | s2 == NULL | s3 == NULL)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		dst[i++] = s2[j++];
	while (s3[k] != '\0')
		dst[i++] = s3[k++];
	dst[i] = '\0';
	return (dst);
}

int	main(int argc, char **argv, char **envp)
{
	char	*command[] = {"ls", "-la", NULL};
	char	**split_path;
	int		i;
	int 	j;
	int		k;
	int		l;

	i = ft_find_path(envp);
	j = 0;
	k = 0;
	l = 0;
	printf("%d\n", ft_find_path(envp));
	printf("%s\n", envp[i]);
	split_path = ft_split(envp[i] + 5, ':');
	while (split_path[j] != NULL)
	{
		split_path[j] = ft_strjoin3(split_path[j], "/", command[0]);
		j++;
	}
	j = 0;
	while (split_path[j] != NULL)
		printf("%s\n", split_path[j++]);
	while (access(split_path[k], F_OK) != 0)
		k++;
	if (execve(split_path[k], command, envp) == -1)
		fprintf(stderr, "Error executing %s\n", split_path[k]);
	printf("done!\n");
	return (0);
}
