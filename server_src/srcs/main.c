#include "server.h"

void		init_socket_fd(t_server *server)
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
			if (strlen(server->fd_array[i].buf_write) > 0)
				FD_SET(i, &server->writefds);
			server->curr_nb = MAX(server->curr_nb, i);
		}
		i++;
	}
}

void		check_fd(t_server *server)
{
	int		i;

	i = 0;
	while ((i < server->max_fd) && (server->ret_select > 0))
	{
		if (FD_ISSET(i, &server->readfds))
			server->fd_array[i].ft_read(server, i);
		if (FD_ISSET(i, &server->writefds))
			server->fd_array[i].ft_write(server, i);
		if (FD_ISSET(i, &server->readfds) || FD_ISSET(i, &server->writefds))
			server->ret_select--;
		i++;
	}
}

void		main_loop(t_server *server)
{
	while (42)
	{
		init_socket_fd(server);
		server->ret_select = select(server->curr_nb + 1,
		&server->readfds, &server->writefds, NULL, NULL);
		check_fd(server);
	}
}

int		main(int ac, char **av)
{
	t_server	server;

	if (ac != 2)
		print_usage(av[0]);
	ft_bzero(&server, sizeof(t_server));
	init_server_config(&server, ft_atoi(av[1]));
	main_loop(&server);
	return (0);
}