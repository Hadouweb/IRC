#include "server.h"

void		set_socket(t_server *server)
{
	int		i;

	i = 0;
	server->curr_nb = 0;
	FD_ZERO(&server->readfds);
	FD_ZERO(&server->writefds);
	while (i < server->max_fd)
	{
		if (server->fd_array[i].type != FREE)
		{
			FD_SET(i, &server->readfds);
			if (ft_strlen(server->fd_array[i].buf_write.buff) > 0)
				FD_SET(i, &server->writefds);
			server->curr_nb = MAX(server->curr_nb, i);
		}
		i++;
	}
}

void	main_loop(t_server *server)
{
	while (42)
	{
		set_socket(server);
		server->ret_select = select(server->curr_nb + 1,
		&server->readfds, &server->writefds, NULL, NULL);
		is_set_socket(server);
	}
}

void	is_set_socket(t_server *server)
{
	int		i;

	i = 0;
	while ((i < server->max_fd) && (server->ret_select > 0))
	{
		if (server->fd_array[i].type == SERVER && FD_ISSET(i, &server->readfds))
			printf("-------------------> readfds server\n");
		if (server->fd_array[i].type == SERVER && FD_ISSET(i, &server->writefds))
			printf("-------------------> writefds server\n");
		if (FD_ISSET(i, &server->readfds))
		{
			server->fd_array[i].ft_read(server, i);
			printf("-------------------> readfds\n");
		}
		if (FD_ISSET(i, &server->writefds))
		{
			server->fd_array[i].ft_write(server, i);
			printf("-------------------> writefds\n");
		}
		if (FD_ISSET(i, &server->readfds) || FD_ISSET(i, &server->writefds))
			server->ret_select--;
		i++;
	}
}
