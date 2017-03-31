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


typedef struct 				s_client
{
	int 					socket;
	struct hostent			*hostname;
	struct sockaddr_in		config;
}							t_client;


#endif