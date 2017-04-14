/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:26:46 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:26:47 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void		set_server_socket(t_server *server)
{
	int					socket_server;
	struct sockaddr_in6	sock_in;
	struct protoent		*protocol;

	protocol = getprotobyname("tcp");
	ft_bzero(&sock_in, sizeof(sock_in));
	if (protocol == NULL)
		print_error_exit("getprotobyname", __FILE__, __LINE__);
	socket_server = socket(PF_INET6, SOCK_STREAM, protocol->p_proto);
	if (socket_server == -1)
		print_error_exit("socket", __FILE__, __LINE__);
	sock_in.sin6_family = AF_INET6;
	sock_in.sin6_addr = in6addr_any;
	sock_in.sin6_port = htons(server->port);
	if (bind(socket_server, (struct sockaddr*)&sock_in, sizeof(sock_in)) == -1)
		print_error_exit("bind", __FILE__, __LINE__);
	if (listen(socket_server, 42) == -1)
		print_error_exit("listen", __FILE__, __LINE__);
	server->fd_array[socket_server].type = SERVER;
	server->fd_array[socket_server].ft_read = event_accept;
}

void			init_server(t_server *server, uint16_t port)
{
	struct rlimit	rlp;
	int				i;

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
	set_server_socket(server);
}
