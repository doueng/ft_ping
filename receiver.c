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
	struct sockaddr_in	sin;
	char				*databuff;

	databuff = xv(ft_memalloc(g_env.data_size), MALLOC);
	ft_bzero(&sin, sizeof(sin));
	msg->msg_name = &sin;
	msg->msg_namelen = sizeof(sin);
	msg->msg_iov = xv(ft_memalloc(sizeof(struct iovec)), MALLOC);
	msg->msg_iovlen = 1;
	msg->msg_iov[0].iov_base = databuff;
	msg->msg_iov[0].iov_len = g_env.data_size;
}

struct icmp	*receiver(struct ip *ip_recv, struct icmp *icmp_recv)
{
	int					ret;
	struct msghdr		msg;
	char				*databuff;

	ft_bzero(&msg, sizeof(msg));
	update_msghdr(&msg);
	databuff = msg.msg_iov[0].iov_base;
	ret = recvmsg(g_env.sockfd, &msg, MSG_WAITALL);
	ft_memcpy(ip_recv, databuff, sizeof(*ip_recv));
	ft_memcpy(icmp_recv, databuff + sizeof(*ip_recv), sizeof(*icmp_recv));
	free(databuff);
	free(msg.msg_iov);
	if (revbytes16(icmp_recv->icmp_type == ICMP_ECHOREPLY))
		g_env.packets_recv += (ret == -1) ? 0 : 1;
	return ((ret == -1) ? NULL : icmp_recv);
}
