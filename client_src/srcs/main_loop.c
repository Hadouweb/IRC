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
	int		s;
	char 	*line;

	s = client->me->socket;
	line = NULL;
	if (FD_ISSET(s, &client->readfds))
		client->me->ft_read(client, s);
	if (FD_ISSET(s, &client->writefds))
		client->me->ft_write(client, s);
	if (FD_ISSET(STDIN_FILENO, &client->readfds) && get_next_line(0, &line) == 1)
	{
		line[ft_strlen(line)] = '\n';
		ring_buffer_write(client, line);
		ft_strdel(&line);
	}
}
