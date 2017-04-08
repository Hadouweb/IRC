#include "server.h"

void	error_cmd(t_server *server, int sc, char *error, char *error2)
{
	event_send_error(server, sc, error, error2);
	event_server_print_log(server, sc, error, error2);
}


void 	cmd(t_server *server, int sc, char *cmd)
{
	if (ft_strncmp(cmd, "/nick ", 6) == 0)
		cmd_nick(server, sc, cmd);
	else if (ft_strncmp(cmd, "/join ", 6) == 0)
		cmd_join(server, sc, cmd);
	else if (ft_strncmp(cmd, "/leave ", 7) == 0)
		cmd_leave(server, sc, cmd);
	else if (ft_strcmp(cmd, "/who\n") == 0)
		cmd_who(server, sc, cmd);
	else if (ft_strncmp(cmd, "/msg ", 5) == 0)
		cmd_msg(server, sc, cmd);
	else
		error_cmd(server, sc, "Error unknown cmd: ", cmd);
	//printf("\t[CMD]\n");
	//printf("\t%s\n", cmd);
}