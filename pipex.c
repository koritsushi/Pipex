/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:51:28 by mliyuan           #+#    #+#             */
/*   Updated: 2024/07/10 15:38:13 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_check_args(t_pipex *data, int argc, char **argv)
{
	if (argc < 5)
	{
		printf("Error! Usage: ");
		printf("./pipex (infile) (command1) (command2) (outfile)\n");
		exit(1);
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
		data->infile_fd = open(argv[1], O_RDONLY, 0777);
	}
	data->outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->outfile_fd == -1)
		ft_error("./pipex: open() error!");
}

/*static void	ft_check_cmds(t_pipex *data, int argc, char **argv, char **envp)
{
	char	**paths;
	char	**cmd;
	char	**arg;
	int		len;

	cmd = ft_split_cmd(data, argc, argv);
	paths = ft_get_path(envp);
	len = ft_strlen_arr(paths);
	ft_get_cmd_path(data, cmd, paths, len);
	arg = ft_get_args_cmd(data, argc, argv);
	ft_split_args_cmd(data, arg);
}*/

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
	printf("hello");
	while (pipe_index <= pipe_count)
	{
		if (pipe(pipe_fd) == -1)
			ft_error("./pipex: pipe() error!");
		data->pipes[pipe_index][read] = pipe_fd[read];
		data->pipes[pipe_index][write] = pipe_fd[write];
		pipe_index++;
		printf("%d\n", pipe_index);
	}
}


static void	ft_execute(t_pipex *data, char **envp)
{
	pid_t	pid;
	int		status;
	int		index;

	status = 0;
	index = 0;
	while (index < data->cmd_count + 1)
	{
		pid = fork();
		if (pid == -1)
			ft_error("./pipex: fork() error!");
		if (pid == 0)
		{
			ft_child_process(data, index, envp);
		}
		else 
		{
			ft_parent_process(data, index);
		}
		index++;
	}
	while (wait(&status) > 0)
		ft_printf("Child process exited, status: %d\n", status);
}

int	main(int argc, char **argv)
{
	t_pipex	data;

	ft_init_data(&data);
	ft_check_args(&data, argc, argv);
	//ft_check_cmds(&data, argc, argv, envp);
	ft_init_pipe(&data, argc);
	//ft_execute(&data, envp);
	//ft_exit_cleanup(&data);
	return (0);
}
