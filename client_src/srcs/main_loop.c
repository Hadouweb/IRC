/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:46:04 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:46:06 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		main_loop(t_client *client)
{
	while (42)
	{
		set_socket(client);
		select(client->me->socket + 1, &client->readfds, &client->writefds,
		NULL, NULL);
		is_set_socket(client);
	}
}

void		print_my_nickname(t_client *client)
{
	ft_putstr("\r                                    ");
	ft_putstr("\r");
	ft_putstr(COLOR_NICK_NAME"<");
	ft_putstr(client->me->nickname);
	ft_putstr(">"COLOR_END);
	ft_putstr(" $> ");
}

void		is_set_socket(t_client *client)
{
	int			s;
	ssize_t		r;
	char		buff[BUF_SIZE + 1];

	s = client->me->socket;
	if (FD_ISSET(s, &client->readfds))
		client->me->ft_read(client, s);
	if (FD_ISSET(s, &client->writefds))
		client->me->ft_write(client, s);
	if (FD_ISSET(STDIN_FILENO, &client->readfds))
	{
		r = read(STDIN_FILENO, buff, BUF_SIZE);
		if (r > 0)
		{
			buff[r] = '\0';
			if (ft_strchr(buff, '\n') != 0)
				print_my_nickname(client);
			ring_buffer_write(client, buff);
		}
	}
}
