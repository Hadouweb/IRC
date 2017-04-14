/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:52:25 by nle-bret          #+#    #+#             */
/*   Updated: 2017/04/14 06:52:27 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>
# include <stdio.h>
# include <ncurses.h>
# include "libft.h"

# define BUF_SIZE	512
# define NICKNAME_SIZE 9
# define MAX(a,b)	((a > b) ? a : b)

# define COLOR_NICK_NAME "\033[33;1m"
# define COLOR_SUCCESS "\033[32;1m"
# define COLOR_ERROR "\033[31;1m"

# define COLOR_END "\033[0m"

enum	e_socket_type
{
	FREE,
	SERVER,
	CLIENT,
};

enum	e_ip_version
{
	IPV4,
	IPV6,
	INVALID,
};

typedef	struct			s_ring_buffer
{
	char				buff[BUF_SIZE + 1];
	int					i;
}						t_ring_buffer;

typedef struct			s_fd
{
	int					socket;
	enum e_socket_type	type;
	void				(*ft_read)();
	void				(*ft_write)();
	char				nickname[NICKNAME_SIZE + 1];
	t_ring_buffer		buf_read;
	t_ring_buffer		buf_write;
}						t_fd;

typedef struct			s_client
{
	t_fd				*me;
	uint16_t			port;
	char				*hostname;
	fd_set				readfds;
	fd_set				writefds;
}						t_client;

void					print_usage(char *prog_name);
void					print_error_exit(char *str, char *file, int line);

void					init_client(t_client *client, char *hostname,
	uint16_t port);

void					event_write(t_client *client, int sc);
void					event_read(t_client *client, int sc);

void					set_socket(t_client *client);
void					main_loop(t_client *client);
void					is_set_socket(t_client *client);

void					ring_buffer_read(t_client *client, char *str);
void					ring_buffer_write(t_client *client, char *str);

void					cmd(t_client *client);
void					cmd_connect(t_client *client, char *cmd);

void					print_my_nickname(t_client *client);

#endif
