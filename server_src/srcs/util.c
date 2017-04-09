#include "server.h"

char 	*get_formated_msg(t_server *server, int sc, char *msg)
{
	char 	*name;

	name = server->fd_array[sc].nickname;
	name = ft_strjoin("\033[33;1m<", name);
	name = ft_strjoin_free(name, "> \033[0m\0", 1);
	msg = ft_strjoin(name, msg);
	return msg;
}

char 	*get_formated_private_msg(t_server *server, int sc, char *msg)
{
	char 	*name;

	name = server->fd_array[sc].nickname;
	name = ft_strjoin("\033[35;1m<", name);
	name = ft_strjoin_free(name, "> \033[0m\0", 1);
	msg = ft_strjoin(name, msg);
	return msg;
}
