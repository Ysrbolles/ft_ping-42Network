# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybolles <ybolles@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 16:33:11 by ybolles           #+#    #+#              #
#    Updated: 2020/12/06 21:08:56 by ybolles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ping
GCC = gcc -c #-Wall -Werror -Wextra
PATH_INC = include/
INC = $(addprefix $(PATH_INC), ft_ping.h)
PATH_INC_LIB = libft/
PATH_SRC = src/
PATH_OBJ = obj/
PATH_LIB = libft/
LIB = -L $(PATH_LIB) -lft

SRC_FILE = main.c \

ALL_OBJ = $(addprefix $(PATH_OBJ), $(SRC_FILE:.c=.o))

DEF = 		\x1B[1;0m
RED = 		\x1B[1;31m
PURPLE =	\x1B[1;34m
BLUE = 		\x1B[1;96m
GREEN = 	\x1B[1;32m
SILVER = 	\x1B[1;90m
YELLOW = 	\x1B[1;33m

define compile
mkdir -p $(PATH_OBJ)
@$(GCC) $1 -o $2 -I $(PATH_INC) -I $(PATH_INC_LIB)
@printf "$(SILVER)[$(PURPLE)Object file$(BLUE) $(notdir $2)$(SILVER)] $(GREEN)Created.$(DEF)\n"
endef

all: $(NAME)

$(NAME): $(ALL_OBJ)
	@make -C $(PATH_LIB)
	@gcc $(ALL_OBJ) -I $(PATH_INC) -I $(PATH_INC_LIB) $(LIB) -o $(NAME)
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
	@printf "$(SILVER)[$(PURPLE)Binnary file$(BLUE) $(NAME) $(SILVER)] $(GREEN)Created.$(DEF)\n"

$(PATH_OBJ)%.o: $(PATH_SRC)%.c $(INC)
	@$(call compile, $< ,$@)

clean:
	@make clean -C $(PATH_LIB)
	@rm -rf $(PATH_OBJ)

fclean: clean
	@make fclean -C $(PATH_LIB)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
