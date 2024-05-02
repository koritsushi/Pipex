/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:51:28 by mliyuan           #+#    #+#             */
/*   Updated: 2024/05/02 16:10:49 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int fd1, int fd2)
{
	
}

void	ft_exec()
{
	int	pipefd[2];

	pipe(pipefd);
	fork();
	if (child)
	{
		dup2()

	}
	else
		close();
}
