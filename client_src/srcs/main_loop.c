#include "client.h"

void		set_socket(t_client *client)
{
	FD_ZERO(&client->readfds);
	FD_ZERO(&client->writefds);
	FD_SET(client->me->socket, &client->readfds);
	if (ft_strlen(client->me->buf_write.buff) > 0)
		FD_SET(client->me->socket, &client->writefds);
	FD_SET(STDIN_FILENO, &client->readfds);
}

void	main_loop(t_client *client)
{
	while (42)
	{
		set_socket(client);
		client->ret_select = select(client->me->socket + 1,
		&client->readfds, &client->writefds, NULL, NULL);
		is_set_socket(client);
	}
}

void	is_set_socket(t_client *client)
{
	int			s;
	ssize_t		r;
	char 		buff[BUF_SIZE + 1];

	s = client->me->socket;
	if (FD_ISSET(s, &client->readfds))
	{
		//printf("client want read\n");
		client->me->ft_read(client, s);
	}
	if (FD_ISSET(s, &client->writefds))
	{
		//printf("client want write\n");
		client->me->ft_write(client, s);
	}
	if (FD_ISSET(STDIN_FILENO, &client->readfds))
	{
		r = read(STDIN_FILENO, buff, BUF_SIZE);
		if (r > 0)
		{
			buff[r] = '\0';
			ring_buffer_write(client, buff);
		}
	}
}
