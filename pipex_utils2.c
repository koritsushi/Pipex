/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:28:24 by mliyuan           #+#    #+#             */
/*   Updated: 2024/11/12 21:50:26 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (path == NULL)
	{
		ft_free(path);
		ft_error("./pipex: path not found!");
	}
	path = ft_format_path(path, "/");
	return (path);
}

char	**ft_format_path(char **path, char *format)
{
	int		i;
	char	**format_path;

	i = 0;
	while (path[i] != NULL)
		i++;
	format_path = malloc(sizeof(char *) * (i + 1));
	if (format_path == NULL)
		ft_error("./pipex: malloc() error!\n");
	i = 0;
	while (path[i] != NULL)
	{
		format_path[i] = ft_strjoin(path[i], format);
		i++;
	}
	format_path[i] = NULL;
	ft_free(path);
	return (format_path);
}

char	***ft_split_cmd(t_pipex *data, char **argv)
{
	char	***cmd;
	int		i;
	int		j;
	int		len;

	j = 0;
	len = 0;
	if (data->here_doc == 1)
		len += 1;
	i = 2 + len;
	cmd = malloc(sizeof(char **) * (data->cmd_count + 1));
	if (cmd == NULL)
		ft_error("./pipex: malloc() error!\n");
	while (argv[i] != NULL && j < data->cmd_count)
	{
		cmd[j] = ft_split(argv[i], ' ');
		i++;
		j++;
	}
	cmd[j] = NULL;
	return (cmd);
}

char	**ft_cmdpath(t_pipex *data, char **path)
{
	int		i;
	int		j;
	int		end;
	char	**cmd_paths;

	i = -1;
	end = ft_str_arr(path);
	cmd_paths = malloc(sizeof(char *) * (data->cmd_count + 1));
	cmd_paths[data->cmd_count] = NULL;
	while (data->cmd_args[++i] != NULL)
	{
		j = -1;
		while (path[++j] != NULL)
		{
			cmd_paths[i] = ft_strjoin(path[j], data->cmd_args[i][0]);
			if (access(cmd_paths[i], F_OK) == 0)
				break ;
			if (j == end - 1)
				ft_cmdpath_free(data, cmd_paths, data->cmd_args[i][0], path);
			free(cmd_paths[i]);
		}
	}
	return (cmd_paths);
}

void	ft_cmdpath_free(t_pipex *data, char **cmd_paths, char *cmd, char **path)
{
	ft_printf("./pipex: %s: command not found!\n", cmd);
	ft_exit_cleanup(data);
	ft_free(cmd_paths);
	ft_free(path);
	exit(1);
}
