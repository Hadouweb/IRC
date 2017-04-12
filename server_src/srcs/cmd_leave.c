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

void	delete_chan(t_list *list, t_channel *chan)
{
	t_link	*n_prev;
	t_link	*n_next;

	if (chan == NULL || list == NULL || ft_strcmp(chan->name, DEFAULT_CHAN) == 0)
		return ;
	printf("delete channel %s\n", chan->name);
	n_prev = chan->link.prev;
	n_next = chan->link.next;
	if (n_prev != NULL && n_next != NULL)
	{
		n_prev->next = n_next;
		n_next->prev = n_prev;
	}
	else if (n_prev != NULL)
	{
		list->tail = n_prev;
		n_prev->next = NULL;
	}
	else if (n_next != NULL)
	{
		list->head = n_next;
		n_next->prev = NULL;
	}
	list->size--;
	free(chan);
	chan = NULL;
}

void		leave_channel(t_server *server, int sc)
{
	if (server->fd_array[sc].curr_chan != NULL)
	{
		server->fd_array[sc].curr_chan->client_connected[sc] = 0;
		server->fd_array[sc].curr_chan->nb_client--;
		if (server->fd_array[sc].curr_chan->nb_client == 0)
			delete_chan(&server->channel_list, server->fd_array[sc].curr_chan);
	}
	//debug_print_all_channel(server);
}

void		try_leave_channel(t_server *server, int sc, char *name)
{
	t_channel	*chan;

	chan = get_channel_by_name(server, name);
	if (chan == NULL)
		send_error(server, sc, name, " is a unknown channel");
	else if (ft_strcmp(DEFAULT_CHAN, name) == 0)
		send_error(server, sc, name, " is the default channel");
	else
		join_channel(server, sc, DEFAULT_CHAN);
}

void		cmd_leave(t_server *server, int sc, char *cmd)
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
