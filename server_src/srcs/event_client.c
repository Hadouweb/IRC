#include "server.h"

void		event_send_all(t_server *server, int sc, char *msg)
{
	int			i;

	i = 0;

	msg = ft_strjoin(server->fd_array[sc].nickname, msg);
	while (i < server->max_fd)
	{
		if ((server->fd_array[i].type == CLIENT) && (i != sc))
			send(i, msg, ft_strlen(msg), 0);
		i++;
	}
}
