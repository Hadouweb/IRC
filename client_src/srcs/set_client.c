#include "client.h"

static void		set_client_socket(t_client *client)
{
	int					socket_client;
	struct protoent		*protocol;

	protocol = getprotobyname("tcp");
	if (protocol == NULL)
		print_error_exit("getprotobyname", __FILE__, __LINE__);
	socket_client = socket(PF_INET, SOCK_STREAM, protocol->p_proto);
	if (socket_client == -1)
		print_error_exit("socket", __FILE__, __LINE__);
	client->entity.ft_read = event_accept;
}

void			init_client(t_client *client, uint16_t port)
{
	client->entity = (t_entity*)malloc(sizeof(t_entity));
	if (client->entity == NULL)
		print_error_exit("malloc", __FILE__, __LINE__);
	ft_bzero(client->entity, sizeof(t_entity));
	client->port = port;
	set_client_socket(client);
}

