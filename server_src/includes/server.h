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

# define BUF_SIZE	512
# define NICKNAME_SIZE 9
# define MAX(a,b)	((a > b) ? a : b)

typedef	struct 			s_ring_buffer
{
	char 				buff[BUF_SIZE + 1];
	int 				i;
}						t_ring_buffer;

typedef struct 			s_fd
{
	enum e_socket_type	type;
	void				(*ft_read)();
	void				(*ft_write)();
	t_ring_buffer		buf_read;
	t_ring_buffer		buf_write;
	char 				nickname[NICKNAME_SIZE + 1];
}						t_fd;

typedef struct 			s_server
{
	t_fd				*fd_array;
	int 				max_fd;
	int 				curr_nb;
	int 				ret_select;
	uint16_t 			port;
	fd_set				readfds;
	fd_set				writefds;
}						t_server;


/*
** ********************************* config.c *********************************
*/
void					init_socket_fd(t_server *server);
void					set_server_config(t_server *server);
void					init_server_config(t_server *server, uint16_t port);
void					set_client(t_server *server, int cs);
void 					set_nickname(t_fd *fd, char *name);

/*
** ********************************* event.c **********************************
*/
void					event_check_socket(t_server *server);

/*
** ********************************* event_client.c ***************************
*/
void					event_send_all(t_server *server, int sc, char *msg);
void					event_send_error(t_server *server, int sc, char *error);

/*
** ********************************* event_server.c ***************************
*/
void					event_server_write(t_server *server, int ss);
void					event_server_read(t_server *server, int ss);
void					event_server_accept(t_server *server, int sc);
void					event_server_print_log(t_server *server, int sc, char *str);

/*
** ********************************* send.c ***********************************
*/

/*
** ********************************* util.c ***********************************
*/
char 					*get_formated_msg(t_server *server, int sc, char *msg);

/*
** ********************************* error.c **********************************
*/
void					print_usage(char *prog_name);
void					print_error_exit(char *str, char *file, int line);

/*
** ********************************* cmd.c ************************************
*/
void 					cmd(t_server *server, int sc, char *cmd);

/*
** ********************************* ring_buffer.c ****************************
*/
void					ring_buffer_read(t_server *server, int cs, char *msg);

#endif