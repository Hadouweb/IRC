#include "server.h"

void	debug_print_channel(void *ptr)
{
	t_channel	*chan;
	int 		i;

	chan = (t_channel*)ptr;
	printf("\tname: %s\n", chan->name);
	printf("\tNumber of clients: %d\n", chan->nb_client);
	printf("\tConnected client: \n");
	i = 0;
	while (i < MAX_CLIENT)
	{
		if (chan->client_connected[i] == 1)
			printf("\t\t%d\n", i);
		i++;
	}
}

void	debug_print_all_channel(t_server *server)
{
	printf("*** debug_print_all_channel ***\n");
	printf("Number of channels: %lu\n", server->channel_list.size);
	ft_list_print(server->channel_list.head, debug_print_channel);
}