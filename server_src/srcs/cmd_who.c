/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:25:22 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:25:23 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char		*concat_name(t_server *server, int i, char *all_name)
{
	if (all_name == NULL)
	{
		all_name = server->fd_array[i].nickname;
		all_name = ft_strjoin(all_name, "\n");
	}
	else
	{
		all_name = ft_strjoin_free(all_name, server->fd_array[i].nickname, 1);
		all_name = ft_strjoin_free(all_name, "\n", 1);
	}
	return (all_name);
}

void			cmd_who(t_server *server, int sc, char *cmd)
{
	t_channel	*chan;
	int			i;
	char		*all_name;

	chan = server->fd_array[sc].curr_chan;
	i = 0;
	all_name = NULL;
	(void)cmd;
	while (i < server->max_fd)
	{
		if (chan->client_connected[i] == 1)
			all_name = concat_name(server, i, all_name);
		i++;
	}
	print_log_success(server, sc, "command /who", NULL);
	action_send_to_client(server, sc, all_name);
	ft_strdel(&all_name);
}
