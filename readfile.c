#include "./libft/libft.h"

void	ft_heredoc(char *delimiter)
{
	char	*res;

	while (1)
	{
		write(STDOUT_FILENO, "here_doc> ", 10);
		res = get_next_line(STDIN_FILENO);
		if (res == NULL || ft_strncmp(res, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(res);
			exit(0);
		}
		ft_putstr_fd(res, 1);
		free(res);
	}
}

int main(int argc, char **argv)
{
	char	*limiter;

	limiter = ft_strdup(argv[2]);
	if (argc >= 2)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			ft_heredoc(limiter);
		}
	}
	return (0);
}