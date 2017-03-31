#include "server.h"

static int		get_socket(void)
{
	int 				s;
	struct protoent		*protocol;

	protocol = getprotobyname("tcp");
	if (protocol == NULL)
		print_error_exit("getprotobyname", __FILE__, __LINE__);
	s = socket(AF_INET, SOCK_STREAM, protocol->p_proto);
	if (s < 0)
		print_error_exit("socket", __FILE__, __LINE__);
	return (s);
}

void			set_server_config(t_server *server, uint16_t port)
{
	int 	ret_bind;
	int 	ret_listen;

	server->socket = get_socket();
	server->config.sin_family = AF_INET;
	server->config.sin_port = htons(port);
	server->config.sin_addr.s_addr = INADDR_ANY;
	ret_bind = bind(server->socket, (struct sockaddr*)&server->config,
					sizeof(server->config));
	if (ret_bind < 0)
		print_error_exit("bind", __FILE__, __LINE__);
	ret_listen = listen(server->socket, 42);
	if (ret_listen != 0)
		print_error_exit("listen", __FILE__, __LINE__);
}
