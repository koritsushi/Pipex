# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/09 09:38:33 by mliyuan           #+#    #+#              #
#    Updated: 2024/06/28 18:49:55 by mliyuan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 		=	pipex_utils.c pipex_utils2.c

FSAN		= 	-fsanitize=address
OBJS		=	$(SRCS:%.c=%.o)
LIBFTDIR	=	./libft
LIBFT		=	$(LIBFTDIR)/libft.a
NAME		=	libft.a
CCFLAGS		=	gcc -Wall -Wextra -Werror
COMPILE		=	gcc -Wall -Wextra -Werror

%.o:%.c
	$(COMPILE) -I. -c $< -o $(<:.c=.o)

all: 		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			cp $(LIBFT) $(NAME)
			ar rcs $(NAME) $(OBJS) $(LIBFT)
			$(CCFLAGS) -g pipex.c $(NAME) -o pipex

$(LIBFT):
			@make -C $(LIBFTDIR) all

clean:
			@make -C $(LIBFTDIR) clean
			@rm -rf $(OBJS)

fclean:		clean
			@make -C $(LIBFTDIR) fclean
			@rm -rf $(NAME)
			@rm -rf ./pipex

re:			fclean all

.PHONY		= all clean fclean re libft fsan
