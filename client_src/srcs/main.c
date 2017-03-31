#include "client.h"

void	print_usage(char *prog_name)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putstr_fd(" hostname", 2);
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

int 	get_socket(void)
{
	int 				s;
	struct protoent		*protocol;

	protocol = getprotobyname("tcp");
	if (protocol == NULL)
		print_error_exit("getprotobyname", __FILE__, __LINE__);
	s = socket(AF_INET, SOCK_STREAM, protocol->p_proto);
	if (s < 0)
		print_error_exit("socket", __FILE__, __LINE__);
	return (s);
}

void	set_client_config(t_client *client, char *hostname, uint16_t port)
{
	client->hostname = gethostbyname(hostname);
	if (client->hostname == NULL)
		print_error_exit("gethostbyname", __FILE__, __LINE__);
	client->config.sin_family = AF_INET;
	client->config.sin_port = htons(port);
	client->config.sin_addr.s_addr = *(uint32_t*)client->hostname->h_addr;
}

void	try_connection(t_client *client)
{
	int 	ret_connect;

	ret_connect = connect(client->socket, (struct sockaddr*)&client->config,
	sizeof(struct sockaddr_in));
	if (ret_connect < 0)
		print_error_exit("connect", __FILE__, __LINE__);
}

void 	receive_message(t_client *client)
{
	int 	ret_recv;
	int 	ret_send;
	char 	buf[12];

	strcpy(buf, "the message");
	ret_send = send(client->socket, buf, sizeof(buf), 0);
	if (ret_send < 0)
		print_error_exit("send", __FILE__, __LINE__);
	ret_recv = recv(client->socket, buf, sizeof(buf), 0);
	if (ret_recv == -1)
		print_error_exit("recv", __FILE__, __LINE__);
}

void	close_socket(t_client *client)
{
	close(client->socket);
}

int		main(int ac, char **av)
{
	t_client	client;

	if (ac != 3)
		print_usage(av[0]);
	ft_bzero(&client, sizeof(t_client));
	client.socket = get_socket();
	set_client_config(&client, av[1], (uint16_t)ft_atoi(av[2]));
	try_connection(&client);
	receive_message(&client);
	close_socket(&client);
	return (0);
}