/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:06:29 by mliyuan           #+#    #+#             */
/*   Updated: 2024/08/28 16:25:45 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_data(t_pipex *data)
{
	data->infile_fd = 0;
	data->outfile_fd = 0;
	data->here_doc = 0;
	data->is_invalid_infile = 0;
	data->cmd_count = 0;
	data->cmd_paths = NULL;
	data->cmd_args = NULL;
}

void	ft_free_arr(char ***str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != NULL)
	{
		while (str[i][j] != NULL)
		{
			free(str[i][j++]);
		}
		i++;
	}
	if (str != NULL)
		free(str);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	if (str != NULL)
		free(str);
}

void	ft_exit_cleanup(t_pipex *data)
{
	int	i;

	i = 0;
	if (data->cmd_paths != NULL)
	{
		ft_free(data->cmd_paths);
	}
	if (data->cmd_args != NULL)
	{
		while (data->cmd_args[i] != NULL)
		{
			ft_free(data->cmd_args[i]);
			i++;
		}
		free(data->cmd_args);
	}
}

void	ft_error(char *error_code)
{
	perror(error_code);
	exit(1);
}
