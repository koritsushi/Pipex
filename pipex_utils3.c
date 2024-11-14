/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:40:30 by mliyuan           #+#    #+#             */
/*   Updated: 2024/11/13 14:15:12 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_str_arr(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != NULL)
		i++;
	return (i);
}

void	ft_cmdpath_free(char **str, int index)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (i <= index)
		free(str[i++]);
	free(str);
}
