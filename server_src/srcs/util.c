#include "server.h"

void	add_client(pid_t pid, t_server *server, int socket, struct sockaddr_in config)
{
	t_client	*client;

	client = (t_client*)malloc(sizeof(t_client));
	if (client == NULL)
		print_error_exit("malloc", __FILE__, __LINE__);
	client->pid = pid;
	client->socket = socket;
	client->config = config;
	client->link.next = NULL;
	client->link.prev = NULL;
	ft_list_push_back(&server->client_list, &client->link);
}

void	handle_client(t_server *server, void (*f)(t_server *, t_client *))
{
	t_link		*client_link;
	t_client	*client;

	client_link = server->client_list.head;
	while (client_link)
	{
		client = PTR_NODE(client_link, t_client, link);
		f(server, client);
		client_link = client_link->next;
	}
}
