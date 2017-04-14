#include "server.h"

static void		check_msg_cmd_client(t_server *server, int sc, char *name, char *msg)
{
	t_fd	*client_dst;

	client_dst = find_client_by_name(server, name);
	if (client_dst == NULL)
		send_error(server, sc, name, " does not exist");
	else
	{
		msg = get_formated_private_msg(server, sc, msg);
		action_send_to_client(server, client_dst->socket, msg);
		ft_strdel(&msg);
	}
}

static void		check_msg_cmd_channel(t_server *server, int sc, char *name, char *msg)
{
	t_channel	*chan;
	t_fd		*client;

	chan = find_channel_by_name(server, name);
	client = &server->fd_array[sc];
	if (chan == NULL)
		send_error(server, sc, name, " does not exist");
	else if (chan->client_connected[client->socket] == 0)
		send_error(server, sc, "You are not on the channel", name);
	else
	{
		action_send_to_chan(server, client->socket, chan, msg);
	}
}


void			cmd_msg(t_server *server, int sc, char *cmd)
{
	char 	*name;
	char 	*msg;
	int 	i;

	if (server && sc)
		;
	i = 5;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	name = &cmd[i];
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\n')
		i++;
	cmd[i] = '\0';
	msg = &cmd[i + 1];
	if (name && name [0] == '#')
		check_msg_cmd_channel(server, sc, name, msg);
	else
		check_msg_cmd_client(server, sc, name, msg);
}

