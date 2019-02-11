/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:00:49 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 12:00:50 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <errno.h>

enum
{
	READ,
	RECV,
	GETPID,
	MALLOC,
	SENDTO,
	SETSOCK,
	SOCKET
};

typedef struct		s_env
{
	int				sockfd;
	struct sockaddr	*dst_addr;
	struct icmp		*icmp_send;
	struct msghdr	*msg;
	struct icmp		*icmp_recv;
	struct ip		*ip;
	size_t			data_size;
	char			*address;
	char			*canonname;
	char			ipstr[INET_ADDRSTRLEN + 1];
	uint16_t		seq;
	size_t			packets_sent;
	size_t			packets_recv;
}					t_env;

extern t_env		g_env;

int					x(int res, int error);
void				*xv(void *res, int error);
void				sig_term(int sigid);
uint16_t			checksum(void *b, int len);
void				main_loop(void);
void				receiver(void);
void				sender(void);
void				create_env(char *address);
unsigned short		checksum(void *b, int len);
void				*x_void(void *res, char *file, int line);
int					x_int(int res, char *file, int line);
void				sig_alarm(int sigid);

#endif
