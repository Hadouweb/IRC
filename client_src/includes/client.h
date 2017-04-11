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
# define MAX(a,b)	((a > b) ? a : b)
enum	e_socket_type
{
	FREE,
	SERVER,
	CLIENT,
};

typedef	struct 			s_ring_buffer
{
	char 				buff[BUF_SIZE + 1];
	int 				i;
}						t_ring_buffer;

typedef struct 			s_fd
{
	int 				socket;
	enum e_socket_type	type;
	void				(*ft_read)();
	void				(*ft_write)();
	t_ring_buffer		buf_read;
	t_ring_buffer		buf_write;
}						t_fd;

typedef struct 			s_client
{
	t_fd				*me;
	int 				ret_select;
	uint16_t 			port;
	char 				*hostname;
	fd_set				readfds;
	fd_set				writefds;
}						t_client;


void					print_usage(char *prog_name);
void					print_error_exit(char *str, char *file, int line);

void					init_client(t_client *client, char *hostname, uint16_t port);

void					event_write(t_client *client, int sc);
void					event_read(t_client *client, int sc);

void					set_socket(t_client *client);
void					main_loop(t_client *client);
void					is_set_socket(t_client *client);

void					ring_buffer_read(t_client *client, char *str);
void					ring_buffer_write(t_client *client, char *str);

void					cmd_connect(t_client *client, char *cmd);

void					print_error(char *error, char *error2);

#endif