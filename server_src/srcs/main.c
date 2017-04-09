#include "server.h"

int		main(int ac, char **av)
{
	t_server	server;

	if (ac != 2)
		print_usage(av[0]);
	ft_bzero(&server, sizeof(t_server));
	init_server(&server, (uint16_t)ft_atoi(av[1]));
	main_loop(&server);
	return (0);
}