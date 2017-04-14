/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:26:23 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:26:25 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		print_log_error(t_server *server, int sc, char *str, char *str2)
{
	ft_putstr(COLOR_ERROR);
	ft_putstr("- [ERROR] from ");
	ft_putstr(COLOR_NICK_NAME);
	ft_putstr("<");
	ft_putstr(server->fd_array[sc].nickname);
	ft_putstr(">"COLOR_ERROR" | ");
	ft_putstr(str);
	if (str2 != NULL)
	{
		ft_putstr(" ");
		ft_putstr(str2);
	}
	ft_putendl(COLOR_END);
}

void		print_log_success(t_server *server, int sc, char *str, char *str2)
{
	ft_putstr(COLOR_SUCCESS);
	ft_putstr("- [SUCCES] ");
	ft_putstr(COLOR_NICK_NAME);
	ft_putstr("<");
	ft_putstr(server->fd_array[sc].nickname);
	ft_putstr(">"COLOR_SUCCESS" ");
	ft_putstr(str);
	if (str2 != NULL)
	{
		ft_putstr(" ");
		ft_putstr(str2);
	}
	ft_putendl(COLOR_END);
}

void		print_log_new_client(t_server *server, int sc,
				struct sockaddr_in *sock_in)
{
	char	*sock;
	char	*port;
	char	*ip;

	sock = ft_itoa(sc);
	port = ft_itoa(ntohs(sock_in->sin_port));
	ip = inet_ntoa(sock_in->sin_addr);
	ft_putstr(COLOR_SUCCESS);
	ft_putstr("- [SUCCES] ");
	ft_putstr("new client: ");
	ft_putstr(COLOR_NICK_NAME);
	ft_putstr(server->fd_array[sc].nickname);
	ft_putstr(COLOR_SUCCESS);
	ft_putstr(" (");
	ft_putstr(sock);
	ft_putstr(") from: ");
	ft_putstr(ip);
	ft_putstr(":");
	ft_putstr(port);
	ft_putendl(COLOR_END);
	ft_strdel(&sock);
	ft_strdel(&port);
}
