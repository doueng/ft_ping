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

void	*x_void(void *res, char *file, int line);
int	x_int(int res, char *file, int line);
void sig_alarm(int sigid);

#endif
