/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:45:45 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:45:47 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			cmd_connect(t_client *client, char *cmd)
{
	int		port;
	char	*hostname;
	int		i;
	int		previous_socket;

	i = 8;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	hostname = &cmd[i];
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\n')
		i++;
	cmd[i] = '\0';
	port = ft_atoi(&cmd[i + 1]);
	if (hostname)
	{
		previous_socket = client->me->socket;
		free(client->me);
		ft_bzero(client, sizeof(t_client));
		init_client(client, hostname, port);
		close(previous_socket);
	}
}
