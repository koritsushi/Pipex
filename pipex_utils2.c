/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:28:24 by mliyuan           #+#    #+#             */
/*   Updated: 2024/06/23 20:15:03 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_process(t_pipex *data, int index, int argc, char **envp)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;

	if (index == 0 && data->is_invalid_infile == 0)
	{
		close(data->pipes[index][read]);
		while (bytes_read = read(data->infile_fd, buffer, BUFFER_SIZE) > 0)
		{
			if (write(data->pipes[index][write], buffer, bytes_read) != bytes_read)
			{
				close(data->infile_fd);
				return ;
			}
		}
		close(data->infile_fd);
		close(data->pipes[index][write]);
	} 
	else if (index == argc - 1)
	{
		close(data->pipes[index][write]);
		while (bytes_read = read(data->pipes[index][read], buffer, BUFFER_SIZE) > 0)
		{	
			if (write(data->outfile_fd, buffer, bytes_read) != bytes_read)
			{
				close(data->outfile_fd);
				return ;
			}
		}
		close(data->outfile_fd);
		close(data->pipes[index][read]);;
	}
}
