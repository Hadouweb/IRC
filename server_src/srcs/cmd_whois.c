/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_whois.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:25:28 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:25:30 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_fd		*get_client_by_name(t_server *server, char *name)
{
	int		i;

	i = 0;
	while (i < server->max_fd)
	{
		if (server->fd_array[i].type == CLIENT)
		{
			if (ft_strcmp(name, server->fd_array[i].nickname) == 0)
				return (&server->fd_array[i]);
		}
		i++;
	}
	return (NULL);
}

static char		*get_chan_by_user(t_server *server, int sc)
{
	t_link		*n;
	t_channel	*chan;
	char		*all_chan;

	n = server->channel_list.head;
	all_chan = NULL;
	(void)cmd;
	while (n)
	{
		chan = PTR_NODE(n, t_channel, link);
		if (chan->client_connected[sc] == 1)
		{
			if (all_chan == NULL)
				all_chan = ft_strdup(chan->name);
			else
				all_chan = ft_strjoin_free(all_chan, chan->name, 1);
			all_chan = ft_strjoin_free(all_chan, "\n", 1);
		}
		n = n->next;
	}
	return (all_chan);
}

static void		prepare_data(t_server *server, int sc, t_fd *client)
{
	char	*rep;
	char	*all_chan;

	rep = ft_strdup("The user ");
	rep = ft_strjoin_free(rep, client->nickname, 1);
	rep = ft_strjoin_free(rep, " is connected at:\n", 1);
	all_chan = get_chan_by_user(server, client->socket);
	if (all_chan)
		rep = ft_strjoin_free(rep, all_chan, 3);
	else
		rep = ft_strjoin_free(rep, " 0 channel", 1);
	print_log_success(server, sc, "command /whois", client->nickname);
	action_send_to_client(server, sc, rep);
	ft_strdel(&rep);
}

void			cmd_whois(t_server *server, int sc, char *cmd)
{
	char	*name;
	t_fd	*client;
	int		i;

	if (server && sc)
		;
	i = 7;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	name = ft_strdup(&cmd[i]);
	i = 0;
	while (name[i] && name[i] != '\n')
		i++;
	name[i] = '\0';
	client = get_client_by_name(server, name);
	if (client == NULL)
		send_error(server, sc, name, "does not exist");
	else
		prepare_data(server, sc, client);
	ft_strdel(&name);
}
