NAME = ft_ping

PATH_SRC = ./src/

PATH_INC = ./includes/

INCLUDES = -I $(PATH_INC)

GCC = gcc
FLAGS = -Wall -Wextra -Werror $(INCLUDES) -g

SRC =	main.c \
		utils.c \
		config.c \
		ping.c \
		print.c \
		lib.c \
		opt.c \

OBJ = $(addprefix $(PATH_SRC), $(SRC:.c=.o))

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(PATH_INC)ft_ping.h
		$(GCC) $(OBJ) -o $(NAME) -lm

clean: 
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all