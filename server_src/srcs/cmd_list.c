#include "server.h"

void		cmd_list(t_server *server, int sc, char *cmd)
{
	t_link		*n;
	t_channel	*chan;
	char 		*all_chan;

	n = server->channel_list.head;
	all_chan = NULL;
	(void)cmd;
	while (n)
	{
		chan = PTR_NODE(n, t_channel, link);
		if (all_chan == NULL)
			all_chan = ft_strdup(chan->name);
		else
			all_chan = ft_strjoin_free(all_chan, chan->name, 1);
		all_chan = ft_strjoin_free(all_chan, " (", 1);
		all_chan = ft_strjoin_free(all_chan, ft_itoa(chan->nb_client), 3);
		all_chan = ft_strjoin_free(all_chan, " users)\n", 1);
		n = n->next;
	}
	print_log_success(server, sc, "command /list", NULL);
	action_send_to_client(server, sc, all_chan);
	ft_strdel(&all_chan);
}
