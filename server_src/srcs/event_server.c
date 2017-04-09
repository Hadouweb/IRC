#include "server.h"

void		event_server_write(t_server *server, int sc)
{
	printf("server_write\n");
	send(sc, server->fd_array[sc].buf_write.buff,
	ft_strlen(server->fd_array[sc].buf_write.buff), 0);
	ft_bzero(&server->fd_array[sc].buf_write, sizeof(t_ring_buffer));
}

void		event_server_read(t_server *server, int sc)
{
	ssize_t		r;
	char 		buff[BUF_SIZE + 1];

	r = recv(sc, buff, BUF_SIZE, 0);
	if (r <= 0)
	{
		leave_channel(server, sc);
		close(sc);
		ft_bzero(&server->fd_array[sc], sizeof(t_fd));
	}
	else
	{
		printf("client #%d write\n", sc);
		buff[r] = '\0';
		ring_buffer_read(server, sc, buff);
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
	set_client_socket(server, sc);
	printf("curr_nb: %d %d\n", server->curr_nb, MAX_CLIENT + 1);
	if (server->curr_nb >= MAX_CLIENT + 1)
	{
		send_error(server, sc, "Sorry the server is full\n", NULL);
		ft_bzero(&server->fd_array[sc], sizeof(t_fd));
		close(sc);
	}
}
