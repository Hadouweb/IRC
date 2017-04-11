#include "client.h"

int		main(int ac, char **av)
{
	t_client	client;

	if (ac != 3)
		print_usage(av[0]);
	ft_bzero(&client, sizeof(t_client));
	init_client(&client, av[1], (uint16_t)ft_atoi(av[2]));
	main_loop(&client);
	return (0);
}
