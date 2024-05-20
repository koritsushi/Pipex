/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:51:28 by mliyuan           #+#    #+#             */
/*   Updated: 2024/05/20 18:44:46 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_init(t_pipex global)
{
	
}

int		ft_redux(char **cmd)
{
	int	i;
	int	j;
	int	command;
	int	pid;
	
	if (pipe(s_pipex->pipefd[0]) == -1);
		return (-1);
	i = -1;
	j = -1;
	while (cmd[i++] != NULL)
	{
		if (access(cmd[i][j++], F_OK) == -1)
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
	t_pipex	global;

	if (argc < 5)
	{	
		printf("Error! Usage: ./pipex (infile) (command1) (command2) (outfile)\n");
		return (0);
	}
	pipex_init(global);
	if (argv[1] == "here_doc")
	{

	}
	else if (open(argv[1], O_READONLY) == -1)
	{	
		printf("pipex: no such file or directory: %s", argc[2]);
		
	}
 
	
	return (0);
}

