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

static void		printer(struct ip *ip_recv, struct icmp *icmp_recv, double triptime)
{
	char src_addr[INET_ADDRSTRLEN + 1];

	(void)icmp_recv;
	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
		ip_recv->ip_len,
		get_ipstr(src_addr, &ip_recv->ip_src),
		icmp_recv->icmp_seq,
		ip_recv->ip_ttl,
		(triptime / 1000.0));
	if (ip_recv->ip_len != g_env.data_size + ICMP_SIZE)
		ft_printf("wrong total length %d instead of %d\n",
				ip_recv->ip_len,
				g_env.data_size + ICMP_SIZE);
}

void			main_loop(void)
{
	struct timeval	send_time;
	struct timeval	recv_time;
	struct icmp		icmp_send;
	struct icmp		icmp_recv;
	struct ip		ip_recv;

	ft_bzero(&icmp_recv, sizeof(icmp_recv));
	sender(&icmp_send);
	gettimeofday(&send_time, NULL);
	receiver(&ip_recv, &icmp_recv);
	gettimeofday(&recv_time, NULL);
	printer(&ip_recv, &icmp_recv, recv_time.tv_usec - send_time.tv_usec);
	alarm(1);
}
