NAME_CLIENT = client
NAME_SERVER = serveur

DIR_CLIENT = ./client_src
DIR_SERVER = ./server_src

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT):
	@make -C $(DIR_CLIENT)
	@cp $(DIR_CLIENT)/$(NAME_CLIENT) .

$(NAME_SERVER):
	@make -C $(DIR_SERVER)
	@cp $(DIR_SERVER)/$(NAME_SERVER) .

clean:
	@make -C $(DIR_CLIENT) clean
	@make -C $(DIR_SERVER) clean

fclean: clean
	@make -C $(DIR_CLIENT) fclean
	@make -C $(DIR_SERVER) fclean
	@/bin/rm -rf $(NAME_CLIENT)
	@/bin/rm -rf $(NAME_SERVER)

re: fclean all

.PHONY: re all clean fclean