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

struct icmp	*receiver(struct ip *ip_recv, struct icmp *icmp_recv)
{
	int					ret;
	struct msghdr		msg;
	struct iovec		iov[1];
	struct sockaddr_in	sin;
	char				*databuff;

	databuff = xv(ft_memalloc(g_env.data_size), MALLOC);
	ft_bzero(&sin, sizeof(sin));
	ft_bzero(&msg, sizeof(msg));
	ft_bzero(iov, sizeof(struct iovec));
	msg.msg_name = &sin;
	msg.msg_namelen = sizeof(sin);
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	/* msg.msg_control = NULL; */
	/* msg.msg_controllen = 0; */
	iov[0].iov_base = databuff;
	iov[0].iov_len = g_env.data_size;
	/* msg.msg_flags = 0; */

	ret = recvmsg(g_env.sockfd, &msg, MSG_WAITALL);
	ft_memcpy(ip_recv, databuff, sizeof(*ip_recv));
	ft_memcpy(icmp_recv, databuff + sizeof(struct ip), ICMP_SIZE);
	if (ret == -1 && errno == EWOULDBLOCK)
	{
		/* fprintf(stderr, " * "); */
		fprintf(stderr,
				"Request timeout for icmp_seq %d\n",
				g_env.seq);
		free(databuff);
		return (NULL);
	}
	g_env.packets_recv++;
	free(databuff);
	return (icmp_recv);
}
