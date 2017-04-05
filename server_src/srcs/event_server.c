#include "server.h"

void		event_server_write(t_server *server, int ss)
{
	//printf("server_write\n");
	if (server && ss)
		;
	//send(socket_fd, server->fd_array[socket_fd].buf_write,
	//ft_strlen(server->fd_array[socket_fd].buf_write), 0);
	//memset(server->fd_array[socket_fd].buf_write, 0, BUF_SIZE + 1);
}

void		event_server_read(t_server *server, int sc)
{
	ssize_t		r;

	r = recv(sc, server->fd_array[sc].buf_read, BUF_SIZE, 0);
	if (r <= 0)
	{
		close(sc);
		ft_bzero(&server->fd_array[sc], sizeof(t_fd));
		printf("client #%d gone away\n", sc);
	}
	else
	{
		server->fd_array[sc].buf_read[r] = '\0';
		ring_buffer_read(server, sc, server->fd_array[sc].buf_read);
		//if (cmd(server, server->fd_array[sc].buf_read) == 0)
		//	event_send_all(server, server->fd_array[sc].buf_read, (size_t)r, sc);
	}
}

void		event_server_accept(t_server *server, int ss)
{
	int					sc;
	struct sockaddr_in	sock_in;
	socklen_t			sock_in_len;

	sock_in_len = sizeof(sock_in);
	sc = accept(ss, (struct sockaddr*)&sock_in, &sock_in_len);
	if (sc == -1)
		print_error_exit("socket", __FILE__, __LINE__);
	printf("New client #%d from %s:%d\n", sc,
		   inet_ntoa(sock_in.sin_addr), ntohs(sock_in.sin_port));
	ft_bzero(&server->fd_array[sc], sizeof(t_fd));
	set_client(server, sc);
}