#include "bircd.h"

int			x_int(int err, int res, char *str, char *file, int line)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s, %d): %s\n",
				str, file, line, strerror(errno));
		exit (1);
	}
	return (res);
}

void		*x_void(void *err, void *res, char *str, char *file, int line)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s, %d): %s\n",
				str, file, line, strerror(errno));
		exit (1);
	}
	return (res);
}

void		clean_fd(t_fd *fd)
{
	fd->type = FD_FREE;
	fd->fct_read = NULL;
	fd->fct_write = NULL;
}

void		check_fd(t_env *e)
{
	int	i;

	i = 0;
	while ((i < e->maxfd) && (e->r > 0))
	{
		if (FD_ISSET(i, &e->fd_read))
			e->fds[i].fct_read(e, i);
		if (FD_ISSET(i, &e->fd_write))
			e->fds[i].fct_write(e, i);
		if (FD_ISSET(i, &e->fd_read) ||
			FD_ISSET(i, &e->fd_write))
			e->r--;
		i++;
	}
}

void		init_fd(t_env *e)
{
	int	i;

	i = 0;
	e->max = 0;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	while (i < e->maxfd)
	{
		if (e->fds[i].type != FD_FREE)
		{
			FD_SET(i, &e->fd_read);
			if (strlen(e->fds[i].buf_write) > 0)
			{
				FD_SET(i, &e->fd_write);
			}
			e->max = MAX(e->max, i);
		}
		i++;
	}
}

void		get_opt(t_env *e, int ac, char **av)
{
	if (ac != 2)
	{
		fprintf(stderr, USAGE, av[0]);
		exit(1);
	}
	e->port = atoi(av[1]);
}

void		init_env(t_env *e)
{
	int				i;
	struct rlimit	rlp;

	X(-1, getrlimit(RLIMIT_NOFILE, &rlp), "getrlimit");
	e->maxfd = rlp.rlim_cur;
	e->fds = (t_fd*)Xv(NULL, malloc(sizeof(*e->fds) * e->maxfd), "malloc");
	i = 0;
	while (i < e->maxfd)
	{
		clean_fd(&e->fds[i]);
		i++;
	}
}

void		srv_create(t_env *e, int port)
{
	int			s;
	struct sockaddr_in	sin;
	struct protoent	*pe;

	pe = (struct protoent*)Xv(NULL, getprotobyname("tcp"), "getprotobyname");
	s = X(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	X(-1, bind(s, (struct sockaddr*)&sin, sizeof(sin)), "bind");
	X(-1, listen(s, 42), "listen");
	e->fds[s].type = FD_SERV;
	e->fds[s].fct_read = srv_accept;
}

void		srv_accept(t_env *e, int s)
{
	int			cs;
	struct sockaddr_in	csin;
	socklen_t		csin_len;

	csin_len = sizeof(csin);
	cs = X(-1, accept(s, (struct sockaddr*)&csin, &csin_len), "accept");
	printf("New client #%d from %s:%d\n", cs,
		   inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	clean_fd(&e->fds[cs]);
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
}

void		client_write(t_env *e, int cs)
{
}

void		client_read(t_env *e, int cs)
{
	int	r;
	int	i;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	else
	{
		i = 0;
		while (i < e->maxfd)
		{
			if ((e->fds[i].type == FD_CLIENT) &&
				(i != cs))
				send(i, e->fds[cs].buf_read, r, 0);
			i++;
		}
	}
}

void		do_select(t_env *e)
{
	e->r = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
}

void		main_loop(t_env *e)
{
	while (1)
	{
		init_fd(e);
		do_select(e);
		check_fd(e);
	}
}


int   		main(int ac, char **av)
{
	t_env   e;

	init_env(&e);
	get_opt(&e, ac, av);
	srv_create(&e, e.port);
	main_loop(&e);
	return (0);
}
