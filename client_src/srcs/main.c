#include "client.h"

int		main(int ac, char **av)
{
	t_client	client;
	char 		*hostname;
	uint16_t 	port;

	hostname = "localhost";
	port = 4242;
	ft_bzero(&client, sizeof(t_client));
	if (ac != 3)
	{
		print_usage(av[0]);
		if (ac == 1)
			init_client(&client, hostname, port);
		else
			exit(1);
	}
	else if (ac == 3)
		init_client(&client, av[1], (uint16_t) ft_atoi(av[2]));
	main_loop(&client);
	return (0);
}
