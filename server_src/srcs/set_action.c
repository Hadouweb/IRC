/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:26:35 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:26:36 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		action_send_to_chan(t_server *server, int sc,
	t_channel *chan, char *msg)
{
	int			i;
	t_fd		*client;

	i = 0;
	msg = get_formated_msg(server, sc, msg);
	if (chan == NULL)
		chan = server->fd_array[sc].curr_chan;
	while (i < server->max_fd)
	{
		client = &server->fd_array[i];
		if (client->curr_chan == chan && client->type == CLIENT && i != sc)
			ring_buffer_write(server, i, msg);
		i++;
	}
	ft_strdel(&msg);
}

void		action_send_to_client(t_server *server, int sc, char *msg)
{
	ring_buffer_write(server, sc, msg);
}

void		action_send_name(t_server *server, int sc)
{
	char	*buff;

	buff = ft_strdup(":");
	buff = ft_strjoin_free(buff, server->fd_array[sc].nickname, 1);
	buff = ft_strjoin_free(buff, "\n", 1);
	ring_buffer_write(server, sc, buff);
	ft_strdel(&buff);
}

void		action_send_error(t_server *server, int sc,
	char *error, char *error2)
{
	(void)server;
	error = ft_strjoin("\033[31;1m", error);
	if (error2 != NULL)
	{
		error = ft_strjoin_free(error, " ", 1);
		error = ft_strjoin_free(error, error2, 1);
	}
	error = ft_strjoin_free(error, "\033[0m\n", 1);
	ring_buffer_write(server, sc, error);
	ft_strdel(&error);
}
