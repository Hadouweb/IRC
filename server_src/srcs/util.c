#include "server.h"

/*void	add_client(t_server *server, int socket, struct sockaddr_in config)
{
	t_client	*client;

	client = (t_client*)malloc(sizeof(t_client));
	if (client == NULL)
		print_error_exit("malloc", __FILE__, __LINE__);
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
}*/

char 	*get_formated_msg(t_server *server, int sc, char *msg)
{
	char 	*name;

	name = server->fd_array[sc].nickname;
	name = ft_strjoin("\033[33;1m<", name);
	name = ft_strjoin_free(name, "> \033[0m\0", 1);
	msg = ft_strjoin(name, msg);
	return msg;
}
