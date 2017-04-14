CC = gcc
FLAG = -Werror -Wextra -Wall -g

LIBFT_PATH = ../libft

SRCS_PATH = ./srcs
INC_PATH = ./includes

HEADER = -I $(LIBFT_PATH)/includes -I $(INC_PATH)

LIB = -L$(LIBFT_PATH) -lft
LIBNAME = $(LIBFT_PATH)/libft.a

SRC =   $(SRCS_PATH)/main.c\
        $(SRCS_PATH)/error.c\
        $(SRCS_PATH)/util.c\
        $(SRCS_PATH)/set_server.c\
        $(SRCS_PATH)/set_client.c\
        $(SRCS_PATH)/main_loop.c\
        $(SRCS_PATH)/event.c\
        $(SRCS_PATH)/set_action.c\
        $(SRCS_PATH)/cmd.c\
        $(SRCS_PATH)/cmd_nick.c\
        $(SRCS_PATH)/cmd_join.c\
        $(SRCS_PATH)/cmd_leave.c\
        $(SRCS_PATH)/cmd_who.c\
        $(SRCS_PATH)/cmd_msg.c\
        $(SRCS_PATH)/cmd_whois.c\
        $(SRCS_PATH)/cmd_list.c\
        $(SRCS_PATH)/ring_buffer.c\
        $(SRCS_PATH)/print_log_bonus.c\
        $(SRCS_PATH)/util_channel.c\

OBJ = $(SRC:.c=.o)

NAME = serveur

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