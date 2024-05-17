/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:56:46 by mliyuan           #+#    #+#             */
/*   Updated: 2024/04/03 22:23:00 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

//linked list
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
void	create_lst(int fd, t_list **lst);
void	add_lines(char *buffer, t_list **lst);
char	*return_line(t_list *lst);
void	clear_lst(t_list **lst);
int		ft_newline(t_list *lst);
int		ft_len_to_newline(t_list *lst);
void	ft_append_line(t_list *lst, char *buffer);
void	ft_lst_dealloc(t_list **lst, t_list *clean_node, char *buffer);
t_list	*ft_lstlast(t_list *lst);

#endif
