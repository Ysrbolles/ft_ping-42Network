# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybolles <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/14 16:25:39 by ybolles           #+#    #+#              #
#    Updated: 2018/10/20 22:12:18 by ybolles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

all: $(NAME)

$(NAME):
	@gcc -c -Wall -Wextra -Werror *.c
	@ar rc $(NAME) *.o
	@ranlib $(NAME)
clean:
	@rm -f *.o
	@rm -f *.gch
fclean: clean
	@rm -f libft.a

re: fclean all
