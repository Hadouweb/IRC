#include "client.h"

void	set_msg(t_client *client, char *msg)
{
	if (msg[0] == '/')
		ring_buffer_write(client, msg);
	else
	{
		ring_buffer_write(client, msg);
		//ring_buffer_write(client, "\n");
	}
}
