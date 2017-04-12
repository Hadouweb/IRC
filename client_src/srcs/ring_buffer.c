#include "client.h"

static void		call_action(t_client *client, char *msg)
{
	(void)client;
	ft_putstr(msg);
}

static void 	convert_buffer(t_client *client, char *ring_buffer)
{
	char 	buffer[BUF_SIZE + 1];
	int 	i;
	int 	j;

	ft_bzero(&buffer, sizeof(buffer));
	i = 0;
	j = 0;
	if (ring_buffer[ft_strlen(ring_buffer) - 1] == '\n')
		call_action(client, ring_buffer);
	else
	{
		while (ring_buffer[i] != '\n')
			i++;
		i++;
		while (j < (int) ft_strlen(ring_buffer))
		{
			if (i >= BUF_SIZE)
				i = 0;
			buffer[j++] = ring_buffer[i++];
		}
		call_action(client, buffer);
	}
}

void			ring_buffer_read(t_client *client, char *str)
{
	int 	i;
	char 	*ring_buffer;

	i = 0;
	ring_buffer = client->me->buf_read.buff;
	while (str[i])
	{
		if (client->me->buf_read.i >= BUF_SIZE)
			client->me->buf_read.i = 0;
		ring_buffer[client->me->buf_read.i] = str[i];
		client->me->buf_read.i++;
		i++;
	}
	if (ft_strchr(ring_buffer, '\n'))
	{
		convert_buffer(client, ring_buffer);
		ft_bzero(&client->me->buf_read, sizeof(t_ring_buffer));
	}
}

void			ring_buffer_write(t_client *client, char *str)
{
	int 	i;
	char 	*ring_buffer;

	i = 0;
	ring_buffer = client->me->buf_write.buff;
	while (str[i])
	{
		if (client->me->buf_write.i >= BUF_SIZE)
			client->me->buf_write.i = 0;
		ring_buffer[client->me->buf_write.i] = str[i];
		client->me->buf_write.i++;
		i++;
	}
}
