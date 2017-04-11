#include "client.h"

void			cmd_connect(t_client *client, char *cmd)
{
	int 	port;
	char 	*hostname;
	int 	i;

	i = 8;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	hostname = &cmd[i];
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\n')
		i++;
	cmd[i] = '\0';
	port = ft_atoi(&cmd[i + 1]);
	printf("hostname: [%s] | port: [%d]\n", hostname, port);
	if (hostname)
	{
		close(client->me->socket);
		ft_bzero(client, sizeof(t_client));
		init_client(client, hostname, port);
	}
}