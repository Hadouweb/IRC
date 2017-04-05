#ifndef SERVER_H
# define SERVER_H

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>
# include <stdio.h>
# include "libft.h"

enum	e_socket_type
{
	FREE,
	SERVER,
	CLIENT,
};

# define BUF_SIZE	4096
# define MAX(a,b)	((a > b) ? a : b)

typedef struct 			s_fd
{
	enum e_socket_type	type;
	void				(*ft_read)();
	void				(*ft_write)();
	char				buf_read[BUF_SIZE + 1];
	char				buf_write[BUF_SIZE + 1];
	char 				nickname[50];
}						t_fd;

typedef	struct 			s_ring_buffer
{
	char 				buff[BUF_SIZE + 1];
	int 				i;
}						t_ring_buffer;

typedef struct 			s_server
{
	t_fd				*fd_array;
	int 				max_fd;
	int 				curr_nb;
	int 				ret_select;
	uint16_t 			port;
	fd_set				readfds;
	fd_set				writefds;
	t_ring_buffer		ring_buffer;
}						t_server;


/*
** ********************************* config.c *********************************
*/
void					init_socket_fd(t_server *server);
void					set_server_config(t_server *server);
void					init_server_config(t_server *server, uint16_t port);
void					set_client(t_server *server, int cs);

/*
** ********************************* event.c **********************************
*/
void					event_check_socket(t_server *server);

/*
** ********************************* event_client.c ***************************
*/
void					event_send_all(t_server *server, int sc, char *msg);

/*
** ********************************* event_server.c ***************************
*/
void					event_server_write(t_server *server, int ss);
void					event_server_read(t_server *server, int ss);
void					event_server_accept(t_server *server, int sc);

/*
** ********************************* send.c ***********************************
*/

/*
** ********************************* util.c ***********************************
*/


/*
** ********************************* error.c **********************************
*/
void					print_usage(char *prog_name);
void					print_error_exit(char *str, char *file, int line);

/*
** ********************************* cmd.c ************************************
*/
int 					cmd(t_server *server, char *str);

/*
** ********************************* ring_buffer.c ****************************
*/
void					ring_buffer_read(t_server *server, int cs, char *msg);

#endif