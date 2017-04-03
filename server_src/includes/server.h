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

typedef struct 				s_fd
{
	enum e_socket_type		type;
	void					(*ft_read)();
	void					(*ft_write)();
	char					buf_read[BUF_SIZE + 1];
	char					buf_write[BUF_SIZE + 1];
}							t_fd;

typedef struct 				s_server
{
	t_fd					*fd_array;
	int 					max_fd;
	int 					curr_nb;
	int 					ret_select;
	uint16_t 				port;
	fd_set					readfds;
	fd_set					writefds;
}							t_server;


/*
** ********************************* config.c *********************************
*/
void						set_server_config(t_server *server);
void						init_server_config(t_server *server, uint16_t port);

/*
** ********************************* event.c **********************************
*/
void						server_accept(t_server *server, int s);


/*
** ********************************* send.c ***********************************
*/

/*
** ********************************* util.c ***********************************
*/


/*
** ********************************* error.c **********************************
*/
void						print_usage(char *prog_name);
void						print_error_exit(char *str, char *file, int line);

#endif