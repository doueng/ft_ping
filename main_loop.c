/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:00:02 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 12:00:02 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void		printer(double triptime)
{
	printf("%zu bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
		g_env.data_size + 8,
		g_env.ipstr,
		g_env.icmp_recv->icmp_seq,
		/* g_env.icmp_recv->icmp_lifetime, */
		g_env.ip->ip_ttl,
		(triptime / 1000.0));
}

static void		update_icmp_send(void)
{
	struct icmp		*icmp_send;

	icmp_send = g_env.icmp_send;
	icmp_send->icmp_seq = g_env.seq++;
	icmp_send->icmp_cksum = 0;
	icmp_send->icmp_cksum = checksum(g_env.icmp_send, sizeof(struct icmp));
}

void			main_loop(void)
{
	struct timeval	send_time;
	struct timeval	recv_time;

	update_icmp_send();
	gettimeofday(&send_time, NULL);
	sender();
	receiver();
	gettimeofday(&recv_time, NULL);
	printer((recv_time.tv_usec - send_time.tv_usec));
	alarm(1);
}
