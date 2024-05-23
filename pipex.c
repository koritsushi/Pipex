/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:51:28 by mliyuan           #+#    #+#             */
/*   Updated: 2024/05/23 16:12:54 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_args()
{
	int		pipe_count; 
	int		pipe_index;
	int		i;
	
	if (argc < 5)
	{	
		printf("Error! Usage: ./pipex (infile) (command1) (command2) (outfile)\n");
		return (0);
	}
	pipe_count = argc - 3;
	pipe = malloc(sizeof(s_pipex) * pipe_count);
	if (argv[1] == "here_doc")
	{
		pipe_count += 1;
	}
	else if (open(argv[1], O_READONLY) == -1)
	{	
		printf("pipex: no such file or directory: %s", argc[2]);
		pipe.infile_fd = open(argv[1], O_RDONLY);
	}
	outfile_fd = open(argv[argc], O_RDWR | O_CREAT | O_TRUN);
 	i = 0;
	pipe_index = 0;
	while (pipe[i])
	{
		pipe[i].in_fd = pipe.pipes[pipe_index][1];
		pipe_index++;
		pipe[i].out_fd = pipe.pipes[pipe_index][0];
		if (i == 1)
		{
			pipe[i].in_fd = pipe.infile_fd;
		}
		else if (i == argc)
		{
			pipe[i].out_fd = pipe.outfile_fd;
		}
	}
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
	struct 	s_pipex *pipe;
	
	ft_check_arg(pipe);

	return (0);
}

