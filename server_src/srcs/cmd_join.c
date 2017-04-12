#include "server.h"

static t_channel	*add_channel(t_server *server, char *name)
{
	t_channel	*chan;

	chan = get_channel_by_name(server, name);
	if (chan != NULL)
		return (chan);
	chan = (t_channel*)malloc(sizeof(t_channel));
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

	leave_channel(server, sc);
	chan = add_channel(server, name);
	chan->client_connected[sc] = 1;
	server->fd_array[sc].curr_chan = chan;
	chan->nb_client++;
	//debug_print_all_channel(server);
}


void				cmd_join(t_server *server, int sc, char *cmd)
{
	char 	*name;
	int 	i;

	if (server && sc)
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
		send_error(server, sc, "The channel name must begin by '#'", NULL);
	else if (ft_strlen(name) > CHANNEL_SIZE)
		send_error(server, sc, "The name is too long (200 characters max)", NULL);
	else if (ft_strlen(name) < 2)
		send_error(server, sc, "The name is too short (2 characters min)", NULL);
	else
		join_channel(server, sc, name);
}

