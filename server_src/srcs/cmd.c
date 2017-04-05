#include "server.h"

int 	cmd(t_server *server, char *str)
{
	if (server)
		;
	if (str[0] == '/')
	{
		printf("CMD: %s\n", str);
		return (1);
	}
	return (0);
}