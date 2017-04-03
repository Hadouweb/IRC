#include "server.h"

/*void	send_to_client(t_server *server, t_client *client, char *msg)
{
	ssize_t 	ret_send;

	(void)server;
	ret_send = send(client->socket, msg, ft_strlen(msg), 0);
	if (ret_send < 0)
		print_error_exit("send", __FILE__, __LINE__);
}*/