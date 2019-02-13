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

# define H_OP 0b1
# define V_OP 0b10

enum
{
	READ,
	RECV,
	GETPID,
	MALLOC,
	SENDTO,
	SETSOCK,
	SOCKET,
	USAGE,
	INVALID_OPTION
};

typedef struct		s_env
{
	struct sockaddr	*dst_addr;
	int				sockfd;
	int				options;
	size_t			data_size;
	uint16_t		seq;
	size_t			packets_sent;
	size_t			packets_recv;
	int				sweepinc;
	int				id;
}					t_env;

extern t_env		g_env;

char				*get_ipstr(char *ipstr, void *addr);
void				receiver(struct ip *ip_recv, struct icmp *icmp_recv);
void				sender(struct icmp *icmp_send);
int					x(int res, int error);
void				*xv(void *res, int error);
void				sig_term(int sigid);
uint16_t			checksum(void *b, int len);
void				main_loop(void);
void				create_env(char *address);
unsigned short		checksum(void *b, int len);
void				*x_void(void *res, char *file, int line);
int					x_int(int res, char *file, int line);
void				sig_alarm(int sigid);

#endif
