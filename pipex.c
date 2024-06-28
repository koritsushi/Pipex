/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:51:28 by mliyuan           #+#    #+#             */
/*   Updated: 2024/06/28 19:01:56 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_check_args(t_pipex *data, int argc, char **argv)
{
	if (argc < 5)
	{
		printf("Error! Usage: ");
		printf("./pipex (infile) (command1) (command2) (outfile)\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		data->here_doc = 1;
	if (open(argv[1], O_RDONLY) == -1)
	{
		printf("pipex: no such file or directory: %s\n", argv[1]);
		data->is_invalid_infile = 1;
	}
	else
	{
		data->infile_fd = open(argv[1], O_RDONLY, 0666);
	}
	data->outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
}

static void	ft_init_pipe(t_pipex *data, int argc)
{
	int		pipe_count;
	int		pipe_index;
	int		pipe_fd[2];

	data->cmd_count = argc - 3;
	pipe_count = data->cmd_count - 1;
	if (data->here_doc == 1)
		pipe_count += 1;
	pipe_index = 0;
	while (pipe_index <= pipe_count)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return ;
		}
		data->pipes[pipe_index][read] = pipe_fd[read];
		data->pipes[pipe_index][write] = pipe_fd[write];
		pipe_index++;
	}
}

static void	ft_check_cmds(t_pipex *data, int argc, char **argv, char **envp)
{
	char	**split_path;
	char	**paths;
	char	**cmd;
	int		i;
	int		j;
	int		len;
	int		index;

	len = 0;
	index = 0;
	cmd = ft_split_cmd(data, argc, argv);
	i = ft_find_path(envp);
	if (i == -1)
		return ;
	paths = ft_split(envp[i] + 5, ':');
	while (paths[len++] != NULL)
		;
	split_path = malloc(sizeof(char *) * (len + 1));
	if (split_path == NULL)
		return ;
	data->cmd_paths = malloc(sizeof(char *) * (data->cmd_count + 1));
	if (data->cmd_paths == NULL)
		return ;
	i = 0;
	while (cmd[i] != NULL && i - 1 <= data->cmd_count)
	{
		j = -1;
		while (paths[++j] != NULL)
			split_path[j] = ft_strjoin3(paths[j], "/", cmd[i]);
		j = -1;
		while (++j < len)
		{
			if (access(split_path[j], F_OK) == 0)
			{
				data->cmd_paths[index] = split_path[j];
				index++;
				break ;
			}
			else if (j == len)
			{
				ft_printf("pipex: command does not exist: %s", cmd[i]);
				(free(split_path), exit(EXIT_FAILURE));
			}
		}
		i++;
	}
	data->cmd_paths[i] = NULL;
	data->cmd_args = argv;
}

static void	ft_execute(t_pipex *data, char **envp)
{
	pid_t	pid;
	int		index;
	int		cmd;

	index = 0;
	cmd = 0;
	while (data->cmd_count > 0)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			ft_child_process(data, index, cmd, envp);
		cmd++;
		index++;
		data->cmd_count--;
	}
	while (wait(NULL) != -1 || errno != ECHILD)
	{
		;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	ft_init_data(&data);
	ft_check_args(&data, argc, argv);
	ft_check_cmds(&data, argc, argv, envp);
	ft_init_pipe(&data, argc);
	ft_execute(&data, envp);
	//ft_exit_cleanup(&data);
	return (0);
}
