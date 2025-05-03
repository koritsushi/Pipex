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

char	*ft_strjoin2(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = -1;
	j = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dst = malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dst == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		dst[i] = s1[i];
	while (s2[++j] != '\0')
	{
		dst[i] = s2[j];
		i++;
	}
	dst[i] = '\0';
	free((char *) s1);
	return (dst);
}

char	*ft_heredoc(char *delimiter)
{
	char	*res;
	char	*final;
	int		i;
	
	i = 0;
	final = NULL;
	while (1)
	{
		write(STDOUT_FILENO, "> ", 3);
		res = get_next_line(STDIN_FILENO);
		if (res == NULL || ft_strncmp(res, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(res);
			break;
		}
		if (i == 0)
			final = ft_strdup(res);
		else
			final = ft_strjoin2(final, res);
		free(res);
		i++;
	}
	return (final);
}

int main(int argc, char **argv)
{
	char	*limiter;

	limiter = ft_strdup(argv[2]);
	if (argc >= 2)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			char *res = ft_heredoc(limiter);
			if (res != NULL)
			{
				ft_printf(res);
				free(res);
			}
		}
	}
	free(limiter);
	return (0);
}