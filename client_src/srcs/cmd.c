#include "client.h"

void			cmd_connect(t_client *client, char *cmd)
{
	int 	port;
	char 	*hostname;
	int 	i;
	int		previous_socket;

	i = 8;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	hostname = &cmd[i];
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\n')
		i++;
	cmd[i] = '\0';
	port = ft_atoi(&cmd[i + 1]);
	if (hostname)
	{
		previous_socket = client->me->socket;
		quit(client);
		ft_bzero(client, sizeof(t_client));
		init_client(client, hostname, port);
		close(previous_socket);
	}
}

void 	cmd(t_client *client)
{
	char	*cmd;

	cmd = client->me->buf_read.buff;
	if (ft_strncmp(cmd, "/quit ", 8) == 0)
		;//cmd_quit(client, cmd);
}
