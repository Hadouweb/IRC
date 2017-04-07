#include "server.h"

void	handle_buf(t_server *server, int sc, char *msg)
{
	if (msg[0] == '/')
	{
		cmd(server, sc, msg);
	}
	else
	{
		printf("\t[MSG]\n");
		printf("\t%s\n", msg);
		event_send_all(server, sc, msg);
	}
}

void 	convert_buffer(t_server *server, int sc)
{
	char 	buffer[BUF_SIZE + 1];
	char 	*ring_buffer;
	int 	i;
	int 	j;

	ft_bzero(&buffer, sizeof(buffer));
	i = 0;
	j = 0;
	ring_buffer = server->ring_buffer.buff;
	if (ring_buffer[ft_strlen(ring_buffer) - 1] == '\n')
		handle_buf(server, sc, ring_buffer);
	else
	{
		while (ring_buffer[i] != '\n')
			i++;
		i++;
		while (j < (int) ft_strlen(ring_buffer)) {
			if (i >= BUF_SIZE)
				i = 0;
			buffer[j++] = ring_buffer[i++];
		}
		handle_buf(server, sc, buffer);
	}
}

void	ring_buffer_read(t_server *server, int sc, char *str)
{
	int 	i;
	char 	*ring_buffer;

	i = 0;
	ring_buffer = server->ring_buffer.buff;
	while (str[i])
	{
		if (server->ring_buffer.i >= BUF_SIZE)
			server->ring_buffer.i = 0;
		ring_buffer[server->ring_buffer.i] = str[i];
		server->ring_buffer.i++;
		i++;
	}
	if (ft_strchr(ring_buffer, '\n'))
	{
		convert_buffer(server, sc);
		ft_bzero(&server->ring_buffer, sizeof(t_ring_buffer));
	}
}