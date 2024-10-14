/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:51:28 by mliyuan           #+#    #+#             */
/*   Updated: 2024/10/14 15:44:56 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_check_args(t_pipex *data, int argc, char **argv)
{
	if (argc < 5)
		ft_error("Usage:./pipex (infile) (command1) (command2) (outfile)\n");
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		data->here_doc = 1;
	if (open(argv[1], O_RDONLY) == -1)
	{
		ft_printf("./pipex: %s: No such file or directory!\n", argv[1]);
		data->infile_fd = open("/dev/null", O_RDONLY);
	}
	else
	{
		data->infile_fd = open(argv[1], O_RDONLY, 0777);
	}
	data->outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->outfile_fd == -1)
		ft_error("./pipex: open() error!\n");
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
	while (pipe_index < pipe_count)
	{
		if (pipe(pipe_fd) == -1)
			ft_error("./pipex: pipe() error!\n");
		data->pipes[pipe_index][READ] = pipe_fd[READ];
		data->pipes[pipe_index][WRITE] = pipe_fd[WRITE];
		pipe_index++;
	}
}

static void	ft_check_cmds(t_pipex *data, char **argv, char **envp)
{
	char	**path;

	path = ft_get_path(envp);
	data->cmd_args = ft_split_cmd(data, argv);
	data->cmd_paths = ft_cmdpath(data, path);
	ft_free(path);
}

static void	ft_process(t_pipex *data, char **envp)
{
	pid_t	pid;
	int		status;
	int		i;

	status = 0;
	i = 0;
	while (i < data->cmd_count)
	{
		pid = fork();
		if (pid == -1)
			ft_error("./pipex: fork() error!\n");
		if (pid == 0)
		{
			ft_child_process(data, i);
			ft_execute(data, data->cmd_paths[i], data->cmd_args[i], envp);
		}
		else
		{
			ft_parent_process(data, i);
		}
		i++;
	}
	while (wait(&status) > 0)
		;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	ft_init_data(&data);
	ft_check_args(&data, argc, argv);
	ft_init_pipe(&data, argc);
	ft_check_cmds(&data, argv, envp);
	ft_process(&data, envp);
	ft_exit_cleanup(&data);
	return (0);
}
