/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:12:21 by mliyuan           #+#    #+#             */
/*   Updated: 2024/05/17 14:05:51 by mliyuan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_pipex
{
	int		pipefd[1024][2];
	t_bool	here_doc;
	t_bool	is_invalid_infile;
	char	**cmd_paths;
	char	***cmd_args;
	int		cmd_count;
}			t_pipex;

#endif
