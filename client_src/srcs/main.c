#include "client.h"

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

int		main(int ac, char **av)
{
	t_client	client;

	if (ac != 3)
		print_usage(av[0]);
	ft_bzero(&client, sizeof(t_client));
	init_client(&client, (uint16_t)ft_atoi(av[1]));
	return (0);
}