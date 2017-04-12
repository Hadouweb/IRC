#include "client.h"


void		event_write(t_client *client, int sc)
{
	if (ft_strncmp(client->me->buf_write.buff, "/connect ", 8) == 0)
	{
		cmd_connect(client, client->me->buf_write.buff);
	}
	else
	{
		send(sc, client->me->buf_write.buff,
		ft_strlen(client->me->buf_write.buff), 0);
	}
	ft_bzero(&client->me->buf_write, sizeof(t_ring_buffer));
}

void		event_read(t_client *client, int sc)
{
	ssize_t		r;
	char 		buff[BUF_SIZE + 1];

	ft_bzero(buff, sizeof(buff));
	r = recv(sc, buff, BUF_SIZE, 0);
	if (r <= 0)
	{
		close(sc);
		ft_bzero(client->me, sizeof(t_fd));
	}
	else
	{
		buff[r] = '\0';
		ring_buffer_read(client, buff);
	}
}
