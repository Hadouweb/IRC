#include "client.h"

static enum e_ip_version 	get_ip_version(char *host)
{
	struct sockaddr_in 	sin4;
	struct sockaddr_in6	sin6;
	int 				ret;

	ret = inet_pton(AF_INET, host, &(sin4.sin_addr));
	if (ret != 0)
		return (IPV4);
	ret = inet_pton(AF_INET6, host, &(sin6.sin6_addr));
	if (ret != 0)
		return (IPV6);
	return (INVALID);
}

static void					set_client_socket(t_client *client)
{
	int					socket_client;
	struct sockaddr_in	sin;
	struct protoent		*protocol;

	protocol = getprotobyname("tcp");
	if (protocol == NULL)
		print_error_exit("getprotobyname", __FILE__, __LINE__);
	socket_client = socket(PF_INET, SOCK_STREAM, protocol->p_proto);
	if (socket_client == -1)
		print_error_exit("socket", __FILE__, __LINE__);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(client->hostname);
	sin.sin_port = htons(client->port);
	if (connect(socket_client, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
		print_error_exit("connect", __FILE__, __LINE__);
	client->me->socket = socket_client;
	client->me->type = CLIENT;
	client->me->ft_read = event_read;
	client->me->ft_write = event_write;
}

static void					set_client_socket6(t_client *client)
{
	int					sc;
	struct sockaddr_in6	sin6;
	struct protoent		*protocol;

	protocol = getprotobyname("tcp");
	if (protocol == NULL)
		print_error_exit("getprotobyname", __FILE__, __LINE__);
	sc = socket(PF_INET6, SOCK_STREAM, protocol->p_proto);
	if (sc == -1)
		print_error_exit("socket", __FILE__, __LINE__);
	sin6.sin6_family = AF_INET6;
	sin6.sin6_addr = in6addr_any;
	sin6.sin6_port = htons(client->port);
	if (connect(sc, (const struct sockaddr *)&sin6, sizeof(sin6)) < 0)
		print_error_exit("connect", __FILE__, __LINE__);
	client->me->socket = sc;
	client->me->type = CLIENT;
	client->me->ft_read = event_read;
	client->me->ft_write = event_write;
}

static char 				*convert_hostname(char *hostname)
{
	if (ft_strcmp(hostname, "localhost") == 0)
		return ("127.0.0.1");
	return (hostname);
}

void						quit(t_client *client)
{
	free(client->me);
}

void						init_client(t_client *client, char *hostname,
	uint16_t port)
{
	enum e_ip_version	ip_version;

	client->me = (t_fd*)malloc(sizeof(t_fd));
	if (client->me == NULL)
		print_error_exit("malloc", __FILE__, __LINE__);
	ft_bzero(client->me, sizeof(t_fd));
	client->port = port;
	client->hostname = convert_hostname(hostname);
	ip_version = get_ip_version(client->hostname);
	if (ip_version == IPV4)
		set_client_socket(client);
	else if (ip_version == IPV6)
		set_client_socket6(client);
	else
		print_error_exit("Incorrect ip format", __FILE__, __LINE__);
}

