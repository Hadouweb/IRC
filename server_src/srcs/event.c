#include "server.h"

void		event_write(t_server *server, int sc)
{
	send(sc, server->fd_array[sc].buf_write.buff,
	ft_strlen(server->fd_array[sc].buf_write.buff), 0);
	ft_bzero(&server->fd_array[sc].buf_write, sizeof(t_ring_buffer));
}

void		event_read(t_server *server, int sc)
{
	ssize_t		r;
	char 		buff[BUF_SIZE + 1];

	r = recv(sc, buff, BUF_SIZE, 0);
	if (r <= 0)
	{
		print_log_success(server, sc, "leave the IRC server", NULL);
		leave_all_channel(server, sc);
		close(sc);
		ft_bzero(&server->fd_array[sc], sizeof(t_fd));
	}
	else
	{
		buff[r] = '\0';
		ring_buffer_read(server, sc, buff);
	}
}

void		event_accept(t_server *server, int ss)
{
	int					sc;
	struct sockaddr_in	sock_in;
	socklen_t			sock_in_len;

	sock_in_len = sizeof(sock_in);
	sc = accept(ss, (struct sockaddr*)&sock_in, &sock_in_len);
	if (sc == -1)
		print_error_exit("socket", __FILE__, __LINE__);
	ft_bzero(&server->fd_array[sc], sizeof(t_fd));
	set_client_socket(server, sc);
	if (server->curr_nb >= MAX_CLIENT + 1)
	{
		send_error(server, sc, "Sorry the server is full", NULL);
		ft_bzero(&server->fd_array[sc], sizeof(t_fd));
		close(sc);
	}
	else
	{
		print_log_new_client(server, sc, &sock_in);
		action_send_name(server, sc);
	}
}
