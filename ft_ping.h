#ifndef FT_PING_H
# define FT_PING_H

# include "./libft/libft.h"
# include <sys/socket.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <netdb.h>
# include <sys/time.h>
# include <signal.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <stdio.h>
# include <sys/time.h>

# define Xv(res)	(x_void(res,__FILE__,__LINE__))
# define X(res)		(x_int(res,__FILE__,__LINE__))

typedef struct		s_env
{
	int				sockfd;
	struct sockaddr	*dst_addr;
	struct icmp		*icmp;
	size_t			data_size;
	char			*address;
	char			*canonname;
	char			ipstr[INET_ADDRSTRLEN + 1];
	uint16_t		seq;
}					t_env;

/* extern uint16_t		g_seq; */
extern t_env		g_env;

struct msghdr		*receiver(int sockfd, struct msghdr	*msg);
void				main_loop(t_env *env);
void				sender(t_env *env);
t_env				*create_env(char *address);
unsigned short		checksum(void *b, int len);
void				*x_void(void *res, char *file, int line);
int					x_int(int res, char *file, int line);
void				sig_alarm(int sigid);

#endif
