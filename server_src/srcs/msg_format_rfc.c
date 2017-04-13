#include "server.h"

void	set_msg(t_server *server, int sc, char *msg)
{
	ring_buffer_write(server, sc, msg);
	//ring_buffer_write(server, sc, "\n");
}
