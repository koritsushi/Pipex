/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:51:28 by mliyuan           #+#    #+#             */
/*   Updated: 2024/06/18 17:34:05 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define read 1
#define write 0

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

	pipe_count = argc - 3;
	if (pipe->here_doc == 1)
		pipe_count += 1;
	pipe->cmd_count = pipe_count - 1;
	pipe_index = 0;
	while (pipe_index <= pipe_count)
	{
		pipe->infile_fd = pipe->pipes[pipe_index][read];
		pipe_index++;
		pipe->outfile_fd = pipe->pipes[pipe_index][write];
		if (pipe_index == 1)
		{
			pipe->pipes[pipe_index][read] = pipe->infile_fd;
		}
		else if (pipe_index == argc)
		{
			pipe->pipes[pipe_index][write] = pipe->outfile_fd;
		}
	}
}

static void	ft_check_cmds(t_pipex *pipe, int argc, char **argv, char **envp)
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
	cmd = ft_split_cmd(pipe, argc, argv);
	i = ft_find_path(envp);
	if (i == -1)
		return ;
	paths = ft_split(envp[i] + 5, ':');
	while (paths[len++] != NULL);
	split_path = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (cmd[i] != NULL)
	{
		j = -1;
		while (paths[++j] != NULL)
			split_path[j] = ft_strjoin3(paths[j], "/", cmd[i]);
		j = -1;
		while (split_path[++j] != NULL)
			len++;
		j = -1;
		while (++j < len)
		{
			if (access(split_path[j], F_OK) == 0)
			{
				ft_strlcpy(pipe->cmd_paths[index], split_path[j], ft_strlen(split_path[j]) + 1);
				index++;
				break;
			} 
			else if (j == len)
			{
				ft_printf("pipex: command does not exist: %s", cmd[i]);
				free(split_path);
				exit(EXIT_FAILURE);
			}
		}
		i++;
	}
	pipe->cmd_paths[index] = NULL; 
}	
/*
static void	ft_execute(t_pipex *pipe, char **envp)
{
	int	i;
	int	index;
	int	cmd;
	int	extra_cmd;
	int	pid;

	i = 0;
	index = 0;
	cmd = 0;
	extra_cmd = 0;
	pid = 0;
	while (wait(NULL) != -1 || errno != ECHILD)
	{
		;
	}
	while (i != pipe->cmd_count)
	{
		pid = fork();
		if (execve(pipe->cmd_args[index], pipe->cmd_args[index][cmd], envp))
		
		i++;
	}
}
*/

int		main(int argc, char **argv, char **envp)
{
	t_pipex pipe;
	
	ft_check_args(&pipe, argc, argv);
	ft_init_pipe(&pipe, argc);
	ft_check_cmds(&pipe, argc, argv, envp);
	//ft_execute(&pipe, envp);
	//ft_exit_cleanup(&pipe);
	return (0);
}
