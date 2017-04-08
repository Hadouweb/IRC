#include "server.h"

int		check_duplicate_name(t_server *server, int sc, char *name)
{
	int 	i;

	i = 0;
	while (i < server->max_fd)
	{
		if ((server->fd_array[i].type == CLIENT) && (i != sc))
		{
			printf("[%s] [%s]\n", name, server->fd_array[i].nickname);
			if (ft_strcmp(name, server->fd_array[i].nickname) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

void	cmd_nick(t_server *server, int sc, char *cmd)
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
	if (ft_strlen(name) > 9)
		send_error(server, sc, "The name is too long (9 characters max)\n", NULL);
	else if (check_duplicate_name(server, sc, name))
		send_error(server, sc, "This name is already taken\n", NULL);
	else
		ft_strcpy(server->fd_array[sc].nickname, name);
}