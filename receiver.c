/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:00:06 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 12:00:07 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	receiver(struct ip *ip_recv, struct icmp *icmp_recv)
{
	int				ret;
	int				i;

	struct msghdr		msg;
	struct iovec		iov[1];
	struct sockaddr_in	sin;
	char				*databuff;

	databuff = xv(ft_memalloc(g_env.data_size), MALLOC);
	ft_bzero(&sin, sizeof(sin));
	msg.msg_name = &sin;
	msg.msg_namelen = sizeof(sin);
	ft_bzero(iov, sizeof(struct iovec));
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	/* msg.msg_control = NULL; */
	/* msg.msg_controllen = 0; */
	char control[1000];
	ft_bzero(control, 1000);
	msg.msg_control = control;
	msg.msg_controllen = 1000;
	iov[0].iov_base = databuff;
	iov[0].iov_len = g_env.data_size;
	msg.msg_flags = 0;
	i = 0;
	while (i++ < 3)
	{
		ret = (recvmsg(g_env.sockfd, &msg, 0));
		if (ret == -1 && errno == EWOULDBLOCK)
		{
			perror(strerror(errno));
			fprintf(stderr, " * ");
			continue ;
		}
		x(ret, RECV);
		ft_memcpy(
			ip_recv,
			databuff,
			sizeof(*ip_recv));
		ft_memcpy(
			icmp_recv,
			databuff + sizeof(struct ip),
			ICMP_MINLEN);
		break ;
	}
	if (i == 3)
		ft_printf("Request timeout for icmp_seq %d\n",
				icmp_recv->icmp_seq);
	// handle error
	g_env.packets_recv++;
	free(databuff);
}
