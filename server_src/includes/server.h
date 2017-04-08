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
# define CHANNEL_SIZE 200
# define MAX_CLIENT 5000
# define DEFAULT_CHAN "#general"
# define MAX(a,b)	((a > b) ? a : b)

typedef	struct 			s_ring_buffer
{
	char 				buff[BUF_SIZE + 1];
	int 				i;
}						t_ring_buffer;

typedef struct			s_channel
{
	t_link				link;
	int 				nb_client;
	char 				name[CHANNEL_SIZE + 1];
	char 				client_connected[MAX_CLIENT];
}						t_channel;

typedef struct 			s_fd
{
	int 				id;
	enum e_socket_type	type;
	void				(*ft_read)();
	void				(*ft_write)();
	t_ring_buffer		buf_read;
	t_ring_buffer		buf_write;
	char 				nickname[NICKNAME_SIZE + 1];
	t_channel			*curr_chan;
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
	t_list				channel_list;
}						t_server;


void					init_socket_fd(t_server *server);
void					set_server_config(t_server *server);
void					init_server_config(t_server *server, uint16_t port);
void					set_new_client(t_server *server, int cs);
void 					send_to_one_client(t_server *server, int sc, char *msg);

void					event_check_socket(t_server *server);

char 					*get_formated_private_msg(t_server *server, int sc, char *msg);
void					cmd_msg(t_server *server, int sc, char *cmd);

void					event_send_all(t_server *server, int sc, char *msg);
void					event_send_error(t_server *server, int sc,
							char *error, char *error2);

void					event_server_write(t_server *server, int ss);
void					event_server_read(t_server *server, int ss);
void					event_server_accept(t_server *server, int sc);
void					event_server_print_log(t_server *server, int sc,
							char *str, char *str2);

char 					*get_formated_msg(t_server *server, int sc, char *msg);
void					delete_chan(t_list *list, t_channel *chan);

void					print_usage(char *prog_name);
void					print_error_exit(char *str, char *file, int line);
void					send_error(t_server *server, int sc, char *error, char *error2);

void 					cmd(t_server *server, int sc, char *cmd);

void					cmd_nick(t_server *server, int sc, char *cmd);

void					cmd_join(t_server *server, int sc, char *cmd);
void					join_channel(t_server *server, int sc, char *name);

t_channel				*get_channel_by_name(t_server *server, char *name);
void					cmd_leave(t_server *server, int sc, char *cmd);
void					cmd_who(t_server *server, int sc, char *cmd);

void					ring_buffer_read(t_server *server, int cs, char *msg);
void					leave_channel(t_server *server, int sc);

void					debug_print_channel(void *ptr);
void					debug_print_all_channel(t_server *server);

#endif