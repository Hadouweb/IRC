#ifndef CLIENT_H
# define CLIENT_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>
# include <stdio.h>
# include "libft.h"

# define BUF_SIZE	512

typedef	struct 			s_ring_buffer
{
	char 				buff[BUF_SIZE + 1];
	int 				i;
}						t_ring_buffer;

typedef struct 			s_entity
{
	int 				id;
	void				(*ft_read)();
	void				(*ft_write)();
	t_ring_buffer		buf_read;
	t_ring_buffer		buf_write;
}						t_entity;

typedef struct 			s_client
{
	t_entity			*entity;
	int 				ret_select;
	uint16_t 			port;
	fd_set				readfds;
	fd_set				writefds;
}						t_client;


void	print_usage(char *prog_name);
void	print_error_exit(char *str, char *file, int line);

void	init_client(t_client *client, uint16_t port);

#endif