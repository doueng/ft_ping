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
# define T_OP 0b100

# define ICMP_SIZE ICMP_MINLEN

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
	SIGNAL,
	INVALID_OPTION
};

enum
{
	MIN,
	TOTAL,
	MAX,
	STDDEV
};

typedef struct		s_packet
{
	float			triptime;
	struct s_packet	*next;
}					t_packet;

typedef struct		s_env
{
	struct sockaddr	*dst_addr;
	struct addrinfo	*addrinfo;
	char			*arg;
	int				sockfd;
	int				options;
	size_t			data_size;
	uint16_t		seq;
	size_t			packets_sent;
	size_t			packets_recv;
	t_packet		*packets;
	int				echoreplys;
	int				id;
	int				ttl;
	double			total_time;
}					t_env;

extern t_env		g_env;

void				set_signals(void);
uint16_t			revbytes16(uint16_t bytes);
void				free_packets(void);
float				roundtrip_min(void);
float				roundtrip_max(void);
float				roundtrip_stddev(void);
float				roundtrip_avg(void);
struct icmp			*receiver(struct ip *ip_recv, struct icmp *icmp_recv);
char				*get_ipstr(char *ipstr, void *addr);
void				sender(struct icmp *icmp_send);
int					x(int res, int error);
void				*xv(void *res, int error);
uint16_t			checksum(void *b, int len);
void				main_loop(void);
void				create_env(char *address);
unsigned short		checksum(void *b, int len);
void				*x_void(void *res, char *file, int line);
int					x_int(int res, char *file, int line);
void				sig_alarm(int sigid);
void				sig_term(int sigid);

#endif
