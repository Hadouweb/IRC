/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:26:03 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:26:05 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		main(int ac, char **av)
{
	t_server	server;

	if (ac != 2)
		print_usage(av[0]);
	ft_bzero(&server, sizeof(t_server));
	init_server(&server, (uint16_t)ft_atoi(av[1]));
	main_loop(&server);
	return (0);
}
