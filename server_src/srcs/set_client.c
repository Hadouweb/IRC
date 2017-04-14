/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:26:41 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:26:42 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			set_client_socket(t_server *server, int sc)
{
	char	*default_name;

	if (server->fd_array[sc].type != SERVER)
	{
		default_name = ft_strjoin_free("Guest", ft_itoa(sc), 2);
		ft_strcpy(server->fd_array[sc].nickname, default_name);
		ft_strdel(&default_name);
		server->fd_array[sc].socket = sc;
		server->fd_array[sc].type = CLIENT;
		server->fd_array[sc].ft_read = event_read;
		server->fd_array[sc].ft_write = event_write;
		join_channel(server, sc, DEFAULT_CHAN);
	}
}
