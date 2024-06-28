/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:12:21 by mliyuan           #+#    #+#             */
/*   Updated: 2024/06/28 19:00:40 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# define read 0
# define write 1

typedef struct s_pipex
{
	int		pipes[1024][2];
	int		infile_fd;
	int		outfile_fd;
	int		here_doc;
	int		is_invalid_infile;
	char	**cmd_paths;
	char	**cmd_args;
	int		cmd_count;
}			t_pipex;

//pipex_utils.c
int		ft_find_path(char **envp);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char	**ft_split_cmd(t_pipex *data, int argc, char **argv);
void	ft_exit_cleanup(t_pipex *data);
void	ft_init_data(t_pipex *data);

//pipex_utils2.c
void	ft_child_process(t_pipex *data, int index, int cmd, char **envp);
void	ft_infile_fd(t_pipex *data, int index);
void	ft_outfile_fd(t_pipex *data, int index);
//void	error(int error_index);
#endif
