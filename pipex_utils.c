/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:06:29 by mliyuan           #+#    #+#             */
/*   Updated: 2024/05/16 19:15:52 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*dst;

	i = -1;
	j = 0;
	k = 0;
	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(s1)+ft_strlen(s2)+ft_strlen(s3)+1));
	if (dst == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		dst[i] = s1[i];
	while (s2[j] != '\0')
		dst[i++] = s2[j++];
	while (s3[k] != '\0')
		dst[i++] = s3[k++];
	dst[i] = '\0';
	return (dst);
}

int	ft_find_path(char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (i);
		i++;
	}
}
