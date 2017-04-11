#include "client.h"

static void		set_client_socket(t_client *client)
{
	int					socket_client;
	struct sockaddr_in	sin;
	struct protoent		*protocol;

	protocol = getprotobyname("tcp");
	if (protocol == NULL)
		print_error_exit("getprotobyname", __FILE__, __LINE__);
	socket_client = socket(PF_INET, SOCK_STREAM, protocol->p_proto);
	if (socket_client == -1)
		print_error_exit("socket", __FILE__, __LINE__);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(client->hostname);
	sin.sin_port = htons(client->port);
	if (connect(socket_client, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
		print_error_exit("connect", __FILE__, __LINE__);
	client->me->socket = socket_client;
	client->me->type = CLIENT;
	client->me->ft_read = event_read;
	client->me->ft_write = event_write;
}

char 			*convert_hostname(char *hostname)
{
	if (ft_strcmp(hostname, "localhost") == 0)
		return ("127.0.0.1");
	return (hostname);
}

void			init_client(t_client *client, char *hostname, uint16_t port)
{
	client->me = (t_fd*)malloc(sizeof(t_fd));
	if (client->me == NULL)
		print_error_exit("malloc", __FILE__, __LINE__);
	ft_bzero(client->me, sizeof(t_fd));
	client->port = port;
	client->hostname = convert_hostname(hostname);
	set_client_socket(client);
}

