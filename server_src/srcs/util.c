#include "server.h"

int 	find_end_msg(char *msg)
{
	char 	*cr;

	cr = ft_strchr(msg, '\n');
	if (cr)
		return (1);
	return (0);
}

char 	*get_formated_msg(t_server *server, int sc, char *msg)
{
	char 	*name;

	name = server->fd_array[sc].nickname;
	//name = ft_strjoin("\033[33;1m<", name);
	name = ft_strjoin(name, " ");
	msg = ft_strjoin(name, msg);
	return (msg);
}

char 	*get_formated_private_msg(t_server *server, int sc, char *msg)
{
	char 	*name;

	name = server->fd_array[sc].nickname;
	//name = ft_strjoin("\033[35;1m<", name);
	name = ft_strjoin(name, " ");
	msg = ft_strjoin(name, msg);
	return (msg);
}
