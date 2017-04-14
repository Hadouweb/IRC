/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:24:58 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:25:00 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_channel	*add_channel(t_server *server, char *name)
{
	t_channel	*chan;

	chan = find_channel_by_name(server, name);
	if (chan != NULL)
		return (chan);
	chan = (t_channel*)malloc(sizeof(t_channel));
	ft_bzero(chan, sizeof(t_channel));
	if (chan == NULL)
		print_error_exit("malloc", __FILE__, __LINE__);
	ft_strcpy(chan->name, name);
	ft_bzero(chan->client_connected, sizeof(chan->client_connected));
	chan->link.next = NULL;
	chan->link.prev = NULL;
	ft_list_push_back(&server->channel_list, &chan->link);
	return (chan);
}

void				join_channel(t_server *server, int sc, char *name)
{
	t_channel	*chan;

	chan = add_channel(server, name);
	server->fd_array[sc].curr_chan = chan;
	if (chan->client_connected[sc] == 0)
	{
		chan->nb_client++;
		chan->client_connected[sc] = 1;
	}
}

void				cmd_join(t_server *s, int sc, char *cmd)
{
	char	*name;
	int		i;

	if (s && sc)
		;
	i = 6;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	name = ft_strdup(&cmd[i]);
	i = 0;
	while (name[i] && name[i] != '\n')
		i++;
	name[i] = '\0';
	if (name[0] != '#')
		send_error(s, sc, "The channel name must begin by '#'", NULL);
	else if (ft_strlen(name) > CHANNEL_SIZE)
		send_error(s, sc, "The name is too long (200 characters max)", NULL);
	else if (ft_strlen(name) < 2)
		send_error(s, sc, "The name is too short (2 characters min)", NULL);
	else
	{
		print_log_success(s, sc, "command /join", name);
		join_channel(s, sc, name);
	}
	ft_strdel(&name);
}
