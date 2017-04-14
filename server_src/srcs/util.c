/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:26:51 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:26:52 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		find_end_msg(char *msg)
{
	char	*cr;

	cr = ft_strchr(msg, '\n');
	if (cr)
		return (1);
	return (0);
}

char	*get_formated_msg(t_server *server, int sc, char *msg)
{
	char	*name;
	char	*m;

	name = ft_strdup(server->fd_array[sc].nickname);
	name = ft_strjoin_free(COLOR_NICK_NAME"<", name, 2);
	name = ft_strjoin_free(name, "> "COLOR_END, 1);
	m = ft_strjoin_free(name, msg, 1);
	return (m);
}

char	*get_formated_private_msg(t_server *server, int sc, char *msg)
{
	char	*name;
	char	*m;

	name = ft_strdup(server->fd_array[sc].nickname);
	name = ft_strjoin_free(COLOR_NICK_NAME_PRIVATE"<", name, 2);
	name = ft_strjoin_free(name, "> "COLOR_END, 1);
	m = ft_strjoin_free(name, msg, 1);
	return (m);
}
