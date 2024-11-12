# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/09 09:38:33 by mliyuan           #+#    #+#              #
#    Updated: 2024/11/12 21:42:48 by mliyuan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 		=	pipex.c			\
				process.c		\
				pipex_utils.c	\
				pipex_utils2.c	\
				pipex_utils3.c

OBJS		=	$(SRCS:%.c=%.o)
LIBFTDIR	=	./libft/
LIBFT		=	$(LIBFTDIR)libft.a
NAME		=	libft.a
PROGRAM		=	pipex
COMPILE		=	gcc
CCFLAGS		=	-Wall -Wextra -Werror -g
DEBUG		=	gddb3
FSAN		= 	-fsanitize=address

%.o:%.c
			$(COMPILE) $(CCFLAGS) -I. -c $< -o $(<:.c=.o)

all: 		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			@cp $(LIBFT) $(NAME)
			ar rcs $(NAME) $(OBJS) $(LIBFT)
			$(COMPILE) $(CCFLAGS) pipex.c $(NAME) -o $(PROGRAM)

$(LIBFT):
			@make -C $(LIBFTDIR) all

clean:
			@make -C $(LIBFTDIR) clean
			@rm -rf $(OBJS)

fclean:		clean
			@make -C $(LIBFTDIR) fclean
			@rm -rf $(NAME)
			@rm -rf $(PROGRAM)

re:			fclean all

.PHONY		= all clean fclean re libft fsan
