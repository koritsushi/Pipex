/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:51:28 by mliyuan           #+#    #+#             */
/*   Updated: 2024/05/23 17:34:04 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_args(s_pipex *pipe, int argc, char **argv)
{	
	if (argc < 5)
	{	
		printf("Error! Usage: ./pipex (infile) (command1) (command2) (outfile)\n");
		exit(EXIT_FAILURE);
	}	
	if (argv[1] == "here_doc")
	{
		pipe_count += 1;
		pipe->here_doc = 1;
	}
	else if (open(argv[1], O_READONLY) == -1)
	{	
		printf("pipex: no such file or directory: %s", argc[2]);
		pipe->is_invalid_infile = 1;
	}
	else
	{
		pipe->infile_fd = open(argv[1], O_RDONLY);
	}
	pipe->outfile_fd = open(argv[argc], O_RDWR | O_CREAT | O_TRUN);
 }

void	ft_init_pipe(s_pipex *pipe, int argc)
{
	int		pipe_count; 
	int		pipe_index;
	int		i;

	pipe_count = argc - 3;
	i = -1;
	pipe_index = 0;
	while (pipe[++i])
	{
		pipe[i]->in_fd = pipe->pipes[pipe_index][1];
		pipe_index++;
		pipe[i]->out_fd = pipe->pipes[pipe_index][0];
		if (i == 1)
		{
			pipe[i]->in_fd = pipe->infile_fd;
		}
		else if (i == argc)
		{
			pipe[i]->out_fd = pipe->outfile_fd;
		}
	}
}

void	ft_check_cmds()
{
	
}

void	ft_redux(char **cmd)
{
	int	i;
	int	j;
	int	command;
	int	pid;
	
	if (pipe(s_pipex->pipefd[0]) == -1);
		return (-1);
	i = -1;
	while (cmd[i++] != NULL)
	{
		if (access(cmd[i++][j], F_OK) == -1)
		{
			ft_printf("pipex: command not found:%s\n" , cmd[i][j]);
			return (-1);
		}
	}
	i = -1;
	j = -1;
	while (command > 0)
	{
		pid = fork();
		if (pid == -1)
			return ;
		ft_execute(cmd[i][j]);
		i++;
		command--;
	}

	while (wait(NULL) != -1 || errno != ECHILD)
	{
		;
	}
}

void	ft_execute(char *cmd)
{
	pid1 = fork();
	if (pid1 == 0)
	{
		close(s_pipex->pipefd[0][0]);
		dup2(s_pipex->pipefd[0][1], STDOUT_FILENO);
	}
	else
	{

	}	
}


int		main(int argc, char **argv, char **envp)
{
	struct s_pipex pipe;
	
	ft_check_arg(&pipe, argc, argv);
	ft_init_pipe(&pipe, argc);
	ft_check_cmds();
	return (0);
}

