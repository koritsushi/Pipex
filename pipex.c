/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:51:28 by mliyuan           #+#    #+#             */
/*   Updated: 2024/05/29 22:41:52 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_check_args(t_pipex *pipe, int argc, char **argv)
{
	if (argc < 5)
	{	
		printf("Error! Usage: ./pipex (infile) (command1) (command2) (outfile)\n");
		exit(EXIT_FAILURE);
	}	
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipe->here_doc = 1;
	}
	else if (open(argv[1], O_RDONLY) == -1)
	{	
		printf("pipex: no such file or directory: %s", argv[2]);
		pipe->is_invalid_infile = 1;
	}
	else
	{
		pipe->infile_fd = open(argv[1], O_RDONLY);
	}
	pipe->outfile_fd = open(argv[argc], O_RDWR | O_CREAT | O_TRUNC);
}

static void	ft_init_pipe(t_pipex *pipe, int argc)
{
	int		pipe_count; 
	int		pipe_index;
	int		i;

	pipe_count = argc - 3;
	if (pipe->here_doc == 1)
		pipe_count += 1;
	pipe->cmd_count = pipe_count - 1;
	i = -1;
	pipe_index = 0;
	while (pipe_index < pipe_count)
	{
		pipe->infile_fd = pipe->pipes[pipe_index][1];
		pipe_index++;
		pipe->outfile_fd = pipe->pipes[pipe_index][0];
		if (i == 1)
		{
			pipe->pipes[pipe_index][1] = pipe->infile_fd;
		}
		else if (i == argc)
		{
			pipe->pipes[pipe_index][0] = pipe->outfile_fd;
		}
	}
}

static void	ft_check_cmds(t_pipex *pipe, int argc, char **argv, char **envp)
{
	char	**split_path;
	char	**cmd;
	int		i;
	int		j;
	int		len;

	cmd = ft_split_cmd(pipe, argc, argv);
	for (int i = 0; cmd[i] != NULL; i++)
		printf("%s\n", cmd[i]);
	i = ft_find_path(envp);
	split_path = NULL;
	pipe->cmd_paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (cmd[i++] != NULL)
	{
		j = -1;
		while (pipe->cmd_paths[j++] != NULL)
			split_path[j] = ft_strjoin3(pipe->cmd_paths[j], "/", cmd[i]);
		j = -1;
		while (split_path[j++] != NULL)
			len++;
		j = -1;
		while (access(split_path[j++], F_OK) != 0)
		{
			if (i == len)
			{
				ft_printf("pipex: command does not exist: %s", cmd[i]);
				exit(EXIT_FAILURE);
			}
		}
	}
	free(split_path);
}

static void	ft_execute()
{
}

int		main(int argc, char **argv, char **envp)
{
	t_pipex pipe;
	
	ft_check_args(&pipe, argc, argv);
	ft_init_pipe(&pipe, argc);
	ft_check_cmds(&pipe, argc, argv, envp);
	ft_execute();
	ft_exit_cleanup(&pipe);
	return (0);
}