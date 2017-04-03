#include "server.h"

void			set_server_config(t_server *server)
{
	int					socket_fd;
	struct sockaddr_in	sock_in;
	struct protoent		*protocol;

	protocol = getprotobyname("tcp");
	if (protocol == NULL)
		print_error_exit("getprotobyname", __FILE__, __LINE__);
	socket_fd = socket(PF_INET, SOCK_STREAM, protocol->p_proto);
	if (socket_fd == -1)
		print_error_exit("socket", __FILE__, __LINE__);
	sock_in.sin_family = AF_INET;
	sock_in.sin_addr.s_addr = INADDR_ANY;
	sock_in.sin_port = htons(server->port);
	if (bind(socket_fd, (struct sockaddr*)&sock_in, sizeof(sock_in)) == -1)
		print_error_exit("bind", __FILE__, __LINE__);
	if (listen(socket_fd, 42) == -1)
		print_error_exit("listen", __FILE__, __LINE__);
	server->fd_array[socket_fd].type = SERVER;
	server->fd_array[socket_fd].ft_read = server_accept;
}

void			init_server_config(t_server *server, uint16_t port)
{
	struct rlimit	rlp;
	int 			i;

	if (getrlimit(RLIMIT_NOFILE, &rlp) == -1)
		print_error_exit("getrlimit", __FILE__, __LINE__);
	server->max_fd = (int)rlp.rlim_cur;
	server->fd_array = (t_fd*)malloc(sizeof(t_fd) * server->max_fd);
	if (server->fd_array == NULL)
		print_error_exit("malloc", __FILE__, __LINE__);
	i = 0;
	while (i < server->max_fd)
	{
		ft_bzero(&server->fd_array[i], sizeof(t_fd));
		i++;
	}
	server->port = port;
	set_server_config(server);
}

