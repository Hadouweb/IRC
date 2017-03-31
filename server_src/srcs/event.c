#include "server.h"

void	event_connection(t_server *server)
{
	pid_t 				pid;
	socklen_t			sock_len;
	struct sockaddr_in	client_config;
	int 				socket_client;

	sock_len = sizeof(struct sockaddr_in);
	server->pid_event = fork();
	if (server->pid_event == 0)
	{
		while (42)
		{
			socket_client = accept(server->socket,
			(struct sockaddr *) &client_config, &sock_len);
			if (socket_client < 0)
				print_error_exit("accept", __FILE__, __LINE__);
			pid = fork();
			if (pid == 0)
			{
				add_client(pid, server, socket_client, client_config);
				break;
			}
		}
	}
}

void 	event_message(t_server *server, t_client *client)
{
	ssize_t 	ret_recv;
	char 		buf[1024];

	(void)server;
	if (client->pid == 0)
	{
		send_to_client(server, client, "$> ");
		while ((ret_recv = recv(client->socket, buf, sizeof(buf), 0)) > 0)
		{
			buf[ret_recv] = '\0';
			printf("Client %d: %s", client->socket,  buf);
			send_to_client(server, client, "$> ");
		}
		if (ret_recv == -1)
			print_error_exit("recv", __FILE__, __LINE__);
	}
}


void	event_close(t_server *server, t_client *client)
{
	(void)server;
	if (client->pid == 0)
	{
		printf("Close %d\n", client->socket);
		close(client->socket);
	}
}