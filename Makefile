# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybolles <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 16:33:11 by ybolles           #+#    #+#              #
#    Updated: 2020/12/04 17:01:30 by ybolles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ping
GCC = gcc -c -Wall -Werror -Wextra
PATH_INC = include/
INC = $(addprefix $(PATH_INC), ft_ping.h)
PATH_SRC = src/
PATH_OBJ = obj/

SRC_FILE = ft_ping.c

ALL_OBJ = $(addprefix $(PATH_OBJ), $(SRC_FILE:.c=.o))

define compile
mkdir -p $(PATH_OBJ)
$(GCC) $1 -o $2 -I $(PATH_INC)
endef

all: $(NAME)

$(NAME): $(ALL_OBJ)
	gcc $(ALL_OBJ) -I $(PATH_INC) -o $(NAME)

$(PATH_OBJ)%.o: $(PATH_SRC)%.c $(INC)
	$(call compile, $< ,$@)

clean:
	rm -rf $(PATH_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
