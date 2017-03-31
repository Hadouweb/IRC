CC = gcc
FLAG = -Werror -Wextra -Wall -g

LIBFT_PATH = ../libft

SRCS_PATH = ./srcs
INC_PATH = ./includes

HEADER = -I $(LIBFT_PATH)/includes -I $(INC_PATH)

LIB = -L$(LIBFT_PATH) -lft
LIBNAME = $(LIBFT_PATH)/libft.a

SRC = $(SRCS_PATH)/main.c\

OBJ = $(SRC:.c=.o)

NAME = client

all: $(NAME)

$(NAME): $(LIBNAME) $(OBJ)
	@$(CC) $(FLAG) $(LIB) -o $(NAME) $^
	@echo "\n\033[39mCompilation done.\033[0m"

$(LIBNAME):
	@make -C $(LIBFT_PATH) -j8

%.o: %.c
	@$(CC) $(FLAG) -o $@ -c $< $(HEADER)
	@echo "\033[34m█\033[0m\c"

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re