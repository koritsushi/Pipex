/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:28:24 by mliyuan           #+#    #+#             */
/*   Updated: 2024/06/26 14:49:58 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_process(t_pipex *data, int index, int argc, char **envp)
{
	
}

void	ft_file_fd(t_pipex *data, int index)
{
	char	*buffer;

	if (index == 0 && data->is_invalid_infile == 0)
	{
		close(data->pipes[index][write]);
		buffer = get_next_line(data->infile_fd);
		if (buffer == NULL)
			return ;
		ft_putstr_fd(buffer, data->pipes[index][read]);
		close(data->infile_fd);
		close(data->pipes[index][read]);
		return ;
	} 
	else if (index == data->cmd_count + 1)
	{
		close(data->pipes[index][read])
		buffer = get_next_line(data->[index][write]);
		if (buffer == NULL)
			return ;
		ft_putstr_fd(buffer, data->outfile_fd);
		close(data->outfile_fd);
		close(data->pipes[index][write]);
		return ;
	}
}
