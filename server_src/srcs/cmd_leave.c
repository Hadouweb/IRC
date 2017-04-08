#include "server.h"

t_channel	*get_channel_by_name(t_server *server, char *name)
{
	t_channel	*chan;
	t_link		*n;

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

void	leave_channel(t_server *server, int sc)
{
	if (server->fd_array[sc].curr_chan != NULL)
	{
		server->fd_array[sc].curr_chan->client_connected[sc] = 0;
		server->fd_array[sc].curr_chan->nb_client--;
		if (server->fd_array[sc].curr_chan->nb_client == 0)
			delete_chan(&server->channel_list, server->fd_array[sc].curr_chan);
	}
	debug_print_all_channel(server);
}

void	try_leave_channel(t_server *server, int sc, char *name)
{
	t_channel	*chan;

	chan = get_channel_by_name(server, name);
	if (chan == NULL)
		send_error(server, sc, name, " is a unknown channel\n");
	else if (ft_strcmp(DEFAULT_CHAN, name) == 0)
		send_error(server, sc, name, " is the default channel\n");
	else
		join_channel(server, sc, DEFAULT_CHAN);
}

void	cmd_leave(t_server *server, int sc, char *cmd)
{
	char 	*name;
	int 	i;

	i = 7;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	name = ft_strdup(&cmd[i]);
	i = 0;
	while (name[i] && name[i] != '\n')
		i++;
	name[i] = '\0';
	try_leave_channel(server, sc, name);
}
