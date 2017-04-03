#include "server.h"

/*void	event_connection(t_server *server)
{
	socklen_t			sock_len;
	struct sockaddr_in	client_config;
	int 				socket_client;

	sock_len = sizeof(struct sockaddr_in);
	//while (42)
	//{
		socket_client = accept(server->socket,
		(struct sockaddr *) &client_config, &sock_len);
		if (socket_client < 0)
			print_error_exit("accept", __FILE__, __LINE__);
		add_client(server, socket_client, client_config);
	//}
}

void 	event_message(t_server *server, t_client *client)
{
	ssize_t 	ret_recv;
	char 		buf[1024];

	(void)server;
	send_to_client(server, client, "$> ");
	while ((ret_recv = recv(client->socket, buf, sizeof(buf), 0)) > 0)
	{
		buf[ret_recv] = '\0';
		printf("Client %d: %s", client->socket,  buf);
		send_to_client(server, client, "$> ");
	}
	if (ret_recv == -1)
		print_error_exit("recv", __FILE__, __LINE__);
}


void	event_close(t_server *server, t_client *client)
{
	(void)server;
	printf("Close %d\n", client->socket);
	close(client->socket);
}*/

void		client_read(t_server *server, int socket_fd)
{
	ssize_t		r;
	int			i;

	r = recv(socket_fd, server->fd_array[socket_fd].buf_read, BUF_SIZE, 0);
	if (r <= 0)
	{
		close(socket_fd);
		ft_bzero(&server->fd_array[socket_fd], sizeof(t_fd));
		printf("client #%d gone away\n", socket_fd);
	}
	else
	{
		i = 0;
		while (i < server->max_fd)
		{
			if ((server->fd_array[i].type == CLIENT) && (i != socket_fd))
				send(i, server->fd_array[socket_fd].buf_read, (size_t)r, 0);
			i++;
		}
	}
}

void		client_write(t_server *server, int socket_fd)
{
	if (server && socket_fd)
		;
}

void		server_accept(t_server *server, int s)
{
	int					socket_fd;
	struct sockaddr_in	sock_in;
	socklen_t			sock_in_len;

	sock_in_len = sizeof(sock_in);
	socket_fd = accept(s, (struct sockaddr*)&sock_in, &sock_in_len);
	if (socket_fd == -1)
		print_error_exit("socket", __FILE__, __LINE__);
	printf("New client #%d from %s:%d\n", socket_fd,
		   inet_ntoa(sock_in.sin_addr), ntohs(sock_in.sin_port));
	ft_bzero(&server->fd_array[socket_fd], sizeof(t_fd));
	server->fd_array[socket_fd].type = CLIENT;
	server->fd_array[socket_fd].ft_read = client_read;
	server->fd_array[socket_fd].ft_write = client_write;
}