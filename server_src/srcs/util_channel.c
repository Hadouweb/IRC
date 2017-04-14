/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_channel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:26:56 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:26:57 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_fd		*find_client_by_name(t_server *server, char *name)
{
	t_fd		*client;
	int			i;

	i = 0;
	while (i < server->max_fd)
	{
		client = &server->fd_array[i];
		if (client->type == CLIENT && ft_strcmp(client->nickname, name) == 0)
			return (client);
		i++;
	}
	return (NULL);
}

t_channel	*find_channel_by_name(t_server *server, char *name)
{
	t_link		*n;
	t_channel	*chan;

	n = server->channel_list.head;
	while (n)
	{
		chan = PTR_NODE(n, t_channel, link);
		if (ft_strcmp(chan->name, name) == 0)
			return (chan);
		n = n->next;
	}
	return (NULL);
}
