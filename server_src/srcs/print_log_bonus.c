#include "server.h"

void		server_print_log(t_server *server, int sc, char *str, char *str2)
{
	(void)server;
	ft_putstr("\033[33;1m");
	ft_putstr(server->fd_array[sc].nickname);
	ft_putstr("\033[0m: ");
	ft_putstr("\033[31;1m");
	ft_putstr(str);
	ft_putstr(" ");
	ft_putstr(str2);
	ft_putstr("\033[0m");
}