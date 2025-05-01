/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:26:22 by mliyuan           #+#    #+#             */
/*   Updated: 2025/05/01 15:26:22 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exitheredoc(char *res)
{
	free(res);
	exit(0);
}

void	ft_heredoc(char *delimiter)
{
	char	*res;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 10);
		res = get_next_line(STDIN_FILENO);
		if (res == NULL)
			ft_exitheredoc(res);
		else if (ft_strncmp(res, delimiter, ft_strlen(delimiter)) == 0)
			ft_exitheredoc(res);
		ft_putstr_fd(res, 1);
		free(res);
	}
}

// int main(int argc, char **argv)
// {
// 	char	*limiter;

// 	limiter = ft_strdup(argv[2]);
// 	if (argc >= 2)
// 	{
// 		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
// 		{
// 			ft_heredoc(limiter);
// 		}
// 	}
// 	return (0);
// }