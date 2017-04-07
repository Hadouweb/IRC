#include "server.h"

void		event_send_all(t_server *server, int sc, char *msg)
{
	int			i;

	i = 0;
	msg = get_formated_msg(server, sc, msg);
	while (i < server->max_fd)
	{
		if ((server->fd_array[i].type == CLIENT) && (i != sc))
			send(i, msg, ft_strlen(msg), 0);
		i++;
	}
}

void		event_send_error(t_server *server, int sc, char *error)
{
	if (server)
		;
	error = ft_strjoin("\033[31;1m", error);
	error = ft_strjoin_free(error, "\033[0m", 1);
	send(sc, error, ft_strlen(error), 0);
}