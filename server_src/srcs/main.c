#include "server.h"

int		main(int ac, char **av)
{
	t_server	server;

	if (ac != 2)
		print_usage(av[0]);
	ft_bzero(&server, sizeof(t_server));
	set_server_config(&server, (uint16_t)ft_atoi(av[1]));
	event_connection(&server);
	handle_client(&server, event_message);
	handle_client(&server, event_close);
	//if (server.pid_event != 0)
	//	printf("LOL\n");
	wait4(-1, &server.status, WUNTRACED | WCONTINUED, NULL);
	return (0);
}