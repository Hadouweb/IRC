#include "server.h"

void	cmd_who(t_server *server, int sc, char *cmd)
{
	t_channel	*chan;
	int 		i;
	char 		*all_name;

	chan = server->fd_array[sc].curr_chan;
	i = 0;
	all_name = NULL;
	(void)cmd;
	while (i < server->max_fd)
	{
		if (chan->client_connected[i] == 1)
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
		}
		i++;
	}
	print_log_success(server, sc, "command /who", NULL);
	action_send_to_client(server, sc, all_name);
	ft_strdel(&all_name);
}
