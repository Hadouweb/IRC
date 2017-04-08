#include "server.h"

t_fd	*find_client_by_name(t_server *server, char *name)
{
	t_fd		*client;
	int 		i;

	i = 0;
	while (i < server->max_fd)
	{
		client = &server->fd_array[i];
		if (client->type == CLIENT && ft_strcmp(client->nickname, name) == 0)
			return (client);
		i++;
	}
	return (NULL);
}

void	check_msg_cmd(t_server *server, int sc, char *name, char *msg)
{
	t_fd	*client_dst;

	client_dst = find_client_by_name(server, name);
	if (client_dst == NULL)
		send_error(server, sc, name, " does not exist\n");
	else if (msg == NULL || ft_strlen(msg) == 0)
		send_error(server, sc, "Can not send an empty message\n", NULL);
	else
	{
		msg = get_formated_private_msg(server, sc, msg);
		send_to_one_client(server, client_dst->id, msg);
	}
}

void	cmd_msg(t_server *server, int sc, char *cmd)
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
	printf("|%s|\n", name);
	msg = &cmd[i + 1];
	printf("MSG: [%s] %d\n", msg, i);
	check_msg_cmd(server, sc, name, msg);
}

