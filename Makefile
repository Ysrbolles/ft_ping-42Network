# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybolles <ybolles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 16:33:11 by ybolles           #+#    #+#              #
#    Updated: 2020/12/29 11:02:45 by ybolles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ping
GCC = gcc -c -Wall -Werror -Wextra
PATH_INC = include/
INC = $(addprefix $(PATH_INC), ft_ping.h)
PATH_INC_LIB = libft/
PATH_SRC = src/
PATH_OBJ = obj/
PATH_LIB = libft/
LIB = -L $(PATH_LIB) -lft

SRC_FILE = main.c \
			ft_ping.c \
			ft_packet.c \
			ft_signals.c 

ALL_OBJ = $(addprefix $(PATH_OBJ), $(SRC_FILE:.c=.o))


define compile
mkdir -p $(PATH_OBJ)
@$(GCC) $1 -o $2 -I $(PATH_INC) -I $(PATH_INC_LIB)
endef

all: $(NAME)

$(NAME): $(ALL_OBJ)
	@make --no-print-directory -C $(PATH_LIB)
	@gcc $(ALL_OBJ) -I $(PATH_INC) -I $(PATH_INC_LIB) $(LIB) -o $(NAME) -lm
	@echo "                                                     Made by : \033[1;91mYbolles\033[m"
	@echo "  ___   _                                    "
	@echo "/ ___) ( )_                _                "
	@echo "| (__  |  _)        _ _   (_)  ___     __   "
	@echo "|  __) | |         (  _ \ | |/  _  \ / _  \ "
	@echo "| |    | |_        | (_) )| || ( ) |( (_) | "
	@echo "(_)     \__)       |  __/ (_)(_) (_) \__  | "
	@echo "            ______ | |              ( )_) |   "
	@echo "           (______)(_)               \___/   "	
	@echo "                     Compilation of $(NAME):  \033[1;32mOK\033[m"

$(PATH_OBJ)%.o: $(PATH_SRC)%.c $(INC)
	@$(call compile, $< ,$@)

clean:
	@make --no-print-directory  clean -C $(PATH_LIB)
	@rm -rf $(PATH_OBJ)

fclean: clean
	@make  --no-print-directory fclean -C $(PATH_LIB)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
