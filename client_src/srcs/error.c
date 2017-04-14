/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:45:49 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:45:50 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	print_usage(char *prog_name)
{
	ft_putstr_fd("Usage: \n[", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putstr_fd(" hostname", 2);
	ft_putstr_fd(" port]\n[", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putstr_fd("] with default hostname (localhost)", 2);
	ft_putstr_fd(" and default port (4242)\n", 2);
}

void	print_error_exit(char *str, char *file, int line)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" in file: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" line: ", 2);
	ft_putnbr_fd(line, 2);
	ft_putchar('\n');
	exit(1);
}
