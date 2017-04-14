/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:26:29 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:26:30 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void		call_action(t_server *server, int sc, char *msg)
{
	char		*tmp_msg;

	tmp_msg = ft_strdup(msg);
	if (msg[0] == '/')
		cmd(server, sc, tmp_msg);
	else
		action_send_to_chan(server, sc, NULL, tmp_msg);
	ft_strdel(&tmp_msg);
}

static void		convert_buffer(t_server *server, int sc)
{
	char	buffer[BUF_SIZE + 1];
	char	*ring_buffer;
	int		i;
	int		j;

	ft_bzero(&buffer, sizeof(buffer));
	i = 0;
	j = 0;
	ring_buffer = server->fd_array[sc].buf_read.buff;
	if (ring_buffer[ft_strlen(ring_buffer) - 1] == '\n')
		call_action(server, sc, ring_buffer);
	else
	{
		while (ring_buffer[i] != '\n')
			i++;
		i++;
		while (j < (int)ft_strlen(ring_buffer))
		{
			if (i >= BUF_SIZE)
				i = 0;
			buffer[j++] = ring_buffer[i++];
		}
		call_action(server, sc, buffer);
	}
}

void			ring_buffer_read(t_server *server, int sc, char *str)
{
	int		i;
	char	*ring_buffer;

	i = 0;
	ring_buffer = server->fd_array[sc].buf_read.buff;
	while (str[i])
	{
		if (server->fd_array[sc].buf_read.i >= BUF_SIZE)
			server->fd_array[sc].buf_read.i = 0;
		ring_buffer[server->fd_array[sc].buf_read.i] = str[i];
		server->fd_array[sc].buf_read.i++;
		i++;
	}
	if (find_end_msg(ring_buffer))
	{
		convert_buffer(server, sc);
		ft_bzero(&server->fd_array[sc].buf_read, sizeof(t_ring_buffer));
	}
}

void			ring_buffer_write(t_server *server, int sc, char *str)
{
	int		i;
	char	*ring_buffer;

	i = 0;
	ring_buffer = server->fd_array[sc].buf_write.buff;
	while (str[i])
	{
		if (server->fd_array[sc].buf_write.i >= BUF_SIZE)
			server->fd_array[sc].buf_write.i = 0;
		ring_buffer[server->fd_array[sc].buf_write.i] = str[i];
		server->fd_array[sc].buf_write.i++;
		i++;
	}
}
