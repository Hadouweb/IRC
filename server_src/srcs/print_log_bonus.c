#include "server.h"

void		print_log_error(t_server *server, int sc, char *str, char *str2)
{
	ft_putstr(COLOR_ERROR);
	ft_putstr("- [ERROR] from ");
	ft_putstr(COLOR_NICK_NAME);
	ft_putstr("<");
	ft_putstr(server->fd_array[sc].nickname);
	ft_putstr(">"COLOR_ERROR" | ");
	ft_putstr(str);
	if (str2 != NULL)
	{
		ft_putstr(" ");
		ft_putstr(str2);
	}
	ft_putendl(COLOR_END);
}

void		print_log_success(t_server *server, int sc, char *str, char *str2)
{
	ft_putstr(COLOR_SUCCESS);
	ft_putstr("- [SUCCES] ");
	ft_putstr(COLOR_NICK_NAME);
	ft_putstr("<");
	ft_putstr(server->fd_array[sc].nickname);
	ft_putstr(">"COLOR_SUCCESS" ");
	ft_putstr(str);
	if (str2 != NULL)
	{
		ft_putstr(" ");
		ft_putstr(str2);
	}
	ft_putendl(COLOR_END);
}

void		print_log_new_client(t_server *server, int sc,
				struct sockaddr_in *sock_in)
{
	ft_putstr(COLOR_SUCCESS);
	ft_putstr("- [SUCCES] ");
	ft_putstr("new client: ");
	ft_putstr(COLOR_NICK_NAME);
	ft_putstr(server->fd_array[sc].nickname);
	ft_putstr(COLOR_SUCCESS);
	ft_putstr(" (");
	ft_putstr(ft_itoa(sc));
	ft_putstr(")");
	ft_putstr(" from: ");
	ft_putstr(inet_ntoa(sock_in->sin_addr));
	ft_putstr(":");
	ft_putstr(ft_itoa(ntohs(sock_in->sin_port)));
	ft_putendl(COLOR_END);
}
