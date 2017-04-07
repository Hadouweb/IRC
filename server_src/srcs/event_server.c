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
	char 		buff[BUF_SIZE + 1];

	r = recv(sc, buff, BUF_SIZE, 0);
	if (r <= 0)
	{
		close(sc);
		ft_bzero(&server->fd_array[sc], sizeof(t_fd));
		printf("client #%d gone away\n", sc);
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
	set_client(server, sc);
}

void		event_server_print_log(t_server *server, int sc, char *str)
{
	if (server)
		;
	ft_putstr("\033[33;1m");
	ft_putstr(server->fd_array[sc].nickname);
	ft_putstr("\033[0m: ");
	ft_putstr("\033[31;1m");
	ft_putstr(str);
	ft_putstr("\033[0m");
}
