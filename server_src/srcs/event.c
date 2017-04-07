#include "server.h"

void		event_check_socket(t_server *server)
{
	int		i;

	i = 0;
	while ((i < server->max_fd) && (server->ret_select > 0))
	{
		if (FD_ISSET(i, &server->readfds))
		{
			server->fd_array[i].ft_read(server, i);
			//printf("readfds\n");
		}
		if (FD_ISSET(i, &server->writefds))
		{
			server->fd_array[i].ft_write(server, i);
			//printf("writefds\n");
		}
		if (FD_ISSET(i, &server->readfds) || FD_ISSET(i, &server->writefds))
			server->ret_select--;
		i++;
	}
}