#include "server.h"

void		main_loop(t_server *server)
{
	while (42)
	{
		init_socket_fd(server);
		server->ret_select = select(server->curr_nb + 1,
		&server->readfds, &server->writefds, NULL, NULL);
		event_check_socket(server);
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