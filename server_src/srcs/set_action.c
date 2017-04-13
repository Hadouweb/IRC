#include "server.h"

void		action_send_all(t_server *server, int sc, char *msg)
{
	int			i;
	t_channel	*chan;
	t_fd		*client;

	i = 0;
	msg = get_formated_msg(server, sc, msg);
	chan = server->fd_array[sc].curr_chan;
	while (i < server->max_fd)
	{
		client = &server->fd_array[i];
		if (chan->client_connected[i] && client->type == CLIENT && i != sc)
			set_msg(server, i, msg);
		i++;
	}
}

void 		action_send_to_one_client(t_server *server, int sc, char *msg)
{
	set_msg(server, sc, msg);
}

void		action_send_name(t_server *server, int sc)
{
	char 	*buff;

	buff = ft_strdup(":");
	buff = ft_strjoin_free(buff, server->fd_array[sc].nickname, 1);
	buff = ft_strjoin_free(buff, "\n", 1);
	set_msg(server, sc, buff);
	ft_strdel(&buff);
}

void		action_send_error(t_server *server, int sc, char *error, char *error2)
{
	(void)server;
	error = ft_strjoin("\033[31;1m", error);
	if (error2 != NULL)
		error = ft_strjoin_free(error, error2, 1);
	error = ft_strjoin_free(error, "\033[0m\n", 1);
	set_msg(server, sc, error);
}