#include "server.h"

void			init_socket_fd(t_server *server)
{
	int		i;

	i = 0;
	server->curr_nb = 0;
	FD_ZERO(&server->readfds);
	FD_ZERO(&server->writefds);
	while (i < server->max_fd)
	{
		if (server->fd_array[i].type != FREE)
		{
			FD_SET(i, &server->readfds);
			if (strlen(server->fd_array[i].buf_write) > 0)
				FD_SET(i, &server->writefds);
			server->curr_nb = MAX(server->curr_nb, i);
		}
		i++;
	}
}

void 			set_nickname(t_fd *fd, char *name)
{
	ft_strcpy(fd->nickname, name);
}

void			set_client(t_server *server, int sc)
{
	char 	*default_name;

	if (server->fd_array[sc].type != SERVER)
	{
		default_name = ft_strjoin_free("Guest", ft_itoa(sc), 2);
		set_nickname(&server->fd_array[sc], default_name);
		server->fd_array[sc].type = CLIENT;
		server->fd_array[sc].ft_read = event_server_read;
		server->fd_array[sc].ft_write = event_server_write;
	}
}

void			set_server_config(t_server *server)
{
	int					socket_server;
	struct sockaddr_in	sock_in;
	struct protoent		*protocol;

	protocol = getprotobyname("tcp");
	if (protocol == NULL)
		print_error_exit("getprotobyname", __FILE__, __LINE__);
	socket_server = socket(PF_INET, SOCK_STREAM, protocol->p_proto);
	if (socket_server == -1)
		print_error_exit("socket", __FILE__, __LINE__);
	sock_in.sin_family = AF_INET;
	sock_in.sin_addr.s_addr = INADDR_ANY;
	sock_in.sin_port = htons(server->port);
	if (bind(socket_server, (struct sockaddr*)&sock_in, sizeof(sock_in)) == -1)
		print_error_exit("bind", __FILE__, __LINE__);
	if (listen(socket_server, 42) == -1)
		print_error_exit("listen", __FILE__, __LINE__);
	server->fd_array[socket_server].type = SERVER;
	server->fd_array[socket_server].ft_read = event_server_accept;
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

