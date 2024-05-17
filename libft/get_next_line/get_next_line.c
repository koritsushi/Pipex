/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:07:27 by mliyuan           #+#    #+#             */
/*   Updated: 2024/04/03 22:24:48 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	create_lst(fd, &lst);
	if (lst == NULL)
		return (NULL);
	buffer = return_line(lst);
	clear_lst(&lst);
	return (buffer);
}

void	create_lst(int fd, t_list **lst)
{
	int		characters_readed;
	char	*buffer;

	while (ft_newline(*lst) == 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		characters_readed = read(fd, buffer, BUFFER_SIZE);
		if (characters_readed == 0)
		{
			free(buffer);
			return ;
		}
		buffer[characters_readed] = '\0';
		add_lines(buffer, lst);
		free(buffer);
	}
}

void	add_lines(char *buffer, t_list **lst)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_lstlast(*lst);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*lst = new_node;
	else
		last_node->next = new_node;
	new_node->content = buffer;
	new_node->next = NULL;
}

char	*return_line(t_list *lst)
{
	char	*buffer;
	int		len;

	len = ft_len_to_newline(lst);
	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == NULL)
		return (NULL);
	ft_append_line(lst, buffer);
	return (buffer);
}

void	clear_lst(t_list **lst)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		j;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	clean_node = malloc(sizeof(t_list));
	if (clean_node == NULL || buffer == NULL)
		return ;
	last_node = ft_lstlast(*lst);
	i = 0;
	j = 0;
	while (last_node->content[i] != '\0')
	{
		if (last_node->content[i] == '\n')
		{
			i++;
			break;
		}
		i++;
	}
	while (last_node->content[i])
	{
		buffer[j] = last_node->content[i];
		j++;
		i++;
	}
	buffer[j] = '\0';
	clean_node->content = buffer;
	clean_node->next = NULL;
	ft_lst_dealloc(lst, clean_node, buffer);
}
