/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:06:29 by mliyuan           #+#    #+#             */
/*   Updated: 2024/06/20 22:51:53 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char 	*dst;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return ;
	dst = malloc(sizeof(char) * (ft_strlen(s1)+ft_strlen(s2)+ft_strlen(s3)+1));
	if (dst == NULL)
		return (NULL);
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

int		ft_find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_split_cmd(t_pipex *data, int argc, char **argv)
{
	char	**cmd;
	char	**tmp;
	int		i;
	int		j;
	int		len;

	len = 0;
	if (data->here_doc == 1)
		len += 1;
	i = 2 + len;
	j = 0;
	cmd = malloc(sizeof(char *) * (argc - 3 + len));
	if (cmd == NULL)
		return (NULL);
	while (argv[i] != NULL && i < argc - 1)
	{
		if (ft_strncmp(argv[i], "here_doc", 8) == 0)
			i++;
		tmp = ft_split(argv[i], ' ');
		cmd[j] = tmp[0];
		i++;
		j++;
	}
	cmd[j] = NULL;
	return (cmd);
}

void	ft_exit_cleanup(t_pipex *data)
{
	int		i;
	int		j;
	int		index;
	int		str;

	i = 0;
	j = 0;
	index = 0;
	str = 0;
	while (i <= (data->cmd_count + data->here_doc + 1))
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
	while (data->cmd_paths[j] != NULL)
	{
		free(data->cmd_paths[j]);
		j++;
	}
	while (data->cmd_args[index] != NULL)
	{
		free(data->cmd_args[index][str]);
		index++;
		str++;
	}
}
