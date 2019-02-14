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

static void	update_msghdr(struct msghdr *msg)
{
	struct iovec		*iov;
	struct sockaddr_in	sin;
	char				*databuff;

	databuff = xv(ft_memalloc(g_env.data_size), MALLOC);
	ft_bzero(&sin, sizeof(sin));
	ft_bzero(msg, sizeof(msg));
	iov = xv(ft_memalloc(sizeof(*iov)), MALLOC);
	msg->msg_name = &sin;
	msg->msg_namelen = sizeof(sin);
	msg->msg_iov = iov;
	msg->msg_iovlen = 1;
	iov[0].iov_base = databuff;
	iov[0].iov_len = g_env.data_size;
}

struct icmp	*receiver(struct ip *ip_recv, struct icmp *icmp_recv)
{
	int					ret;
	struct msghdr		msg;
	char				*databuff;

	update_msghdr(&msg);
	databuff = msg.msg_iov[0].iov_base;
	ret = recvmsg(g_env.sockfd, &msg, MSG_WAITALL);
	ft_memcpy(ip_recv, databuff, sizeof(*ip_recv));
	ft_memcpy(icmp_recv, databuff + sizeof(struct ip), ICMP_SIZE);
	if (ret == -1 && errno == EWOULDBLOCK)
	{
		fprintf(stderr,
				"Request timeout for icmp_seq %d\n",
				g_env.seq);
		free(msg.msg_iov);
		free(databuff);
		return (NULL);
	}
	g_env.packets_recv++;
	free(databuff);
	free(msg.msg_iov);
	return (icmp_recv);
}
