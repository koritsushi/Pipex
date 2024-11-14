/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:12:21 by mliyuan           #+#    #+#             */
/*   Updated: 2024/11/13 13:49:56 by mliyuan          ###   ########.fr       */
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
# define READ 0
# define WRITE 1

typedef struct s_pipex
{
	int		pipes[1024][2];
	int		infile_fd;
	int		outfile_fd;
	int		here_doc;
	char	**cmd_paths;
	char	***cmd_args;
	int		cmd_count;
	int		index;
}			t_pipex;

//pipex_utils.c
void	ft_init_data(t_pipex *data);
void	ft_free(char **str);
void	ft_free_arr(char ***str);
void	ft_exit_cleanup(t_pipex *data);
void	ft_error(char *error_code);

//pipex_utils2.c
char	**ft_get_path(char **envp);
char	**ft_format_path(char **path, char *format);
char	***ft_split_cmd(t_pipex *data, char **argv);
void	ft_cmdpath(t_pipex *data, char **path);
void	\
ft_cmdpath_error(t_pipex *data, char *cmd_args, char **path);

//pipex_utils3.c
int		ft_str_arr(char **str);
void	ft_cmdpath_free(char **str, int index);

//process.c
void	ft_parent_process(t_pipex *data, int index);
void	ft_child_process(t_pipex *data, int index);
void	\
ft_execute(t_pipex *data, char *cmd_paths, char **cmd_args, char **envp);

#endif
