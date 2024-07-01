/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:28:24 by mliyuan           #+#    #+#             */
/*   Updated: 2024/07/01 22:27:37 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen_arr(char **str)
{
	int	len;

	if (str == NULL)
		return (-1);
	len = 0;
	while (str[len] != NULL)
		len++;
	return (len);
}

void	ft_cmds_access(t_pipex *data, int index, char **split_path, char *cmd)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen_arr(split_path);
	while (++i < len)
	{
		if (access(split_path[i], F_OK) == 0)
		{
			data->cmd_paths[index] = split_path[i];
			break ;
		}
		else if (i == len)
		{
			ft_printf("pipex: command does not exist: %s", cmd);
			(free(split_path), exit(EXIT_FAILURE));
		}
	}
}

void	ft_get_cmd_path(t_pipex *data, char **cmd, char **paths, int len)
{
	char	**split_path;
	int		index;
	int		i;
	int		j;

	split_path = malloc(sizeof(char *) * (len + 1));
	if (split_path == NULL)
		ft_error("./pipex: malloc() error!");
	data->cmd_paths = malloc(sizeof(char *) * (data->cmd_count + 1));
	if (data->cmd_paths == NULL)
		ft_error("./pipex: malloc() error!");
	i = 0;
	index = 0;
	while (cmd[i] != NULL && i - 1 <= data->cmd_count)
	{
		j = -1;
		while (paths[++j] != NULL)
			split_path[j] = ft_strjoin3(paths[j], "/", cmd[i]);
		ft_cmds_access(data, index, split_path, cmd[i]);
		index++;
		i++;
	}
	data->cmd_paths[i] = NULL;
}

char	**ft_get_args_cmd(t_pipex *data, int argc, char **argv)
{
	int		cmd_index;
	int		argv_index;
	char	**arg;

	cmd_index = 0;
	argv_index = 2;
	arg = malloc(sizeof(char *) * (data->cmd_count + 1));
	if (arg == NULL)
		ft_error("./pipex: malloc() error!");
	while (argv[argv_index] != NULL && argv_index < argc - 1)
		arg[cmd_index++] = ft_strdup(argv[argv_index++]);
	arg[cmd_index] = NULL;
	return (arg);
}

void	ft_split_args_cmd(t_pipex *data, char **arg)
{
	int	index;

	index = 0;
	data->cmd_args = malloc(sizeof(char **) * (data->cmd_count + 1));
	if (data->cmd_args == NULL)
		ft_error("./pipex: malloc() error!");
	while (arg[index] != NULL)
		data->cmd_args[index] = ft_split(arg[index], ' ');
	data->cmd_args[index] = NULL;
}