#include "server.h"

void	error_nickname(t_server *server, int sc, char *error)
{
	event_send_error(server, sc, error);
	event_server_print_log(server, sc, error);
}

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

void	cmd_nickname(t_server *server, int sc, char *cmd)
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
		error_nickname(server, sc, "The name is too long (9 characters max)\n");
	else if (check_duplicate_name(server, sc, name))
		error_nickname(server, sc, "This name is already taken\n");
	else
		set_nickname(&server->fd_array[sc], name);
}

void 	cmd(t_server *server, int sc, char *cmd)
{
	if (ft_strncmp(cmd, "/nick ", 6) == 0)
		cmd_nickname(server, sc, cmd);
	//printf("\t[CMD]\n");
	//printf("\t%s\n", cmd);
}