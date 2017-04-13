#include "client.h"

int 	only_letter_or_number(char *msg)
{
	int 	i;
	int 	size;

	i = 0;
	size = (int)ft_strlen(msg);
	if (msg[0] == '/')
		i++;
	while (i < size && msg[i] != ' ')
	{
		if (!(
				(msg[i] >= 'a' && msg[i] <= 'z') ||
			 	(msg[i] >= 'A' && msg[i] <= 'Z') ||
			 	(msg[i] >= '0' && msg[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

void	set_cmd(t_client *client, char *msg)
{
	if (msg != NULL && only_letter_or_number(msg) == 1)
	{
		ring_buffer_write(client, msg);
		//ring_buffer_write(client, "\n");
	}
}

void	set_msg(t_client *client, char *msg)
{
	if (msg[0] == '/')
		set_cmd(client, msg);
	else
	{
		ring_buffer_write(client, msg);
		//ring_buffer_write(client, "\n");
	}
}
