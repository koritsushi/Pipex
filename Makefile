# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/09 09:38:33 by mliyuan           #+#    #+#              #
#    Updated: 2024/05/09 09:46:19 by mliyuan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 		=	

OBJS		=	$(SRCS:%.c=%.o)
LIBFTDIR	=	./libft
LIBFT		=	$(LIBFTDIR)/libft.a
NAME		=	libftprintf.a
CCFLAGS		=	gcc -Wall -Wextra -Werror

%.o:%.c
		%(CCFLAGS) -I. -c $< -o $@

all: $(NAME)

$(NAME):	%(LIBFT) %(OBJS)
			cp $(LIBFT) $(NAME)
			ar rcs $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
			make -C $(LIBFTDIR) all

clean:
			@make -C $(LIBFTDIR) clean
			@rm -rf $(OBJS)

fclean:		clean
			@make -C $(LIBFTDIR) fclean
			@rm -rf $(NAME)

re: fclean all

.PHONY		= all clean fclean re libft
