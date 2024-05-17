/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:31:01 by mliyuan           #+#    #+#             */
/*   Updated: 2024/04/03 22:54:03 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_newline(t_list *lst)
{
	int	i;

	if (lst == NULL)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->content[i] != '\0' && i < BUFFER_SIZE)
		{
			if (lst->content[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_len_to_newline(t_list *lst)
{
	int	i;
	int len;

	if (lst == NULL)
		return (0);
	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		lst = lst->next;
	}
	return (len);
}

void	ft_append_line(t_list *lst, char *buffer)
{
	int	i;
	int	j;

	while (lst)
	{
		i = 0;
		while (lst->content[i] != '\0')
		{
			if (lst->content[i] == '\n')
			{
				buffer[j++] = '\n';
				buffer[j] = '\0';
				return ;
			}
			buffer[j] = lst->content[i];
			j++;
			i++;
		}
		lst = lst->next;
	}
	buffer[j] = '\0';
}

void	ft_lst_dealloc(t_list **lst, t_list *clean_node, char *buffer)
{
	t_list	*tmp;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
	if (clean_node->content[0])
		*lst = clean_node;
	else
	{
		free(buffer);
		free(clean_node);
	}
}