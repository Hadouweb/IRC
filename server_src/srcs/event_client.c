#include "server.h"

void		event_send_all(t_server *server, int sc, char *msg)
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
		{
			send(i, msg, ft_strlen(msg), 0);
		}
		i++;
	}
}

void 		send_to_one_client(t_server *server, int sc, char *msg)
{
	if (server)
		;
	send(sc, msg, ft_strlen(msg), 0);
}

void		event_send_error(t_server *server, int sc, char *error, char *error2)
{
	if (server)
		;
	error = ft_strjoin("\033[31;1m", error);
	if (error2 != NULL)
		error = ft_strjoin_free(error, error2, 1);
	error = ft_strjoin_free(error, "\033[0m", 1);
	send(sc, error, ft_strlen(error), 0);
}