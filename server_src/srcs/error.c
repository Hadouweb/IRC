#include "server.h"

void	print_usage(char *prog_name)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putstr_fd(" port\n", 2);
	exit(1);
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

void	send_error(t_server *server, int sc, char *error, char *error2)
{
	action_send_error(server, sc, error, error2);
	server_print_log(server, sc, error, error2);
}
