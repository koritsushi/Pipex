/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:51:28 by mliyuan           #+#    #+#             */
/*   Updated: 2024/05/17 12:27:27 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{	
		printf("Error! Usage: ./pipex (infile) (command1) (command2) (outfile)\n");
		return (0);
	}
	else if (open(argv[2], O_READONLY) == -1)
		printf("pipex: no such file or directory: %s", argc[2]);

	
	return (0);
}
