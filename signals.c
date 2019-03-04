/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:00:14 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 12:00:14 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void			set_signals(void)
{
	if (SIG_ERR == signal(SIGALRM, sig_alarm) ||
		SIG_ERR == signal(SIGINT, sig_term))
		x(-1, SIGNAL);
}

void			sig_alarm(int sigid)
{
	if (sigid != SIGALRM)
		return ;
	main_loop();
}

static double	calc_packet_loss(double pkt_sent, double pkt_recv)
{
	pkt_sent = pkt_sent == 0 ? 1 : pkt_sent;
	return (((pkt_sent - pkt_recv) / pkt_sent) * 100);
}

static void		ft_freeaddr(void)
{
	struct addrinfo	*curr;
	struct addrinfo *tmp;

	curr = g_env.addrinfo;
	while (curr)
	{
		tmp = curr->ai_next;
		free(curr->ai_canonname);
		free(curr);
		curr = tmp;
	}
}

void			sig_term(int sigid)
{
	if (sigid != SIGINT)
		return ;
	alarm(0);
	printf("--- %s ping statistics ---\n", g_env.arg);
	printf(
		"%zu packets transmitted, %zu received, %.1f%% packet loss, ",
		g_env.packets_sent,
		g_env.packets_recv,
		calc_packet_loss(g_env.packets_sent, g_env.packets_recv));
	printf("time %zums\n", (size_t)g_env.total_time);
	if (g_env.echoreplys > 0)
	{
		printf("rtt min/avg/max/stddev = ");
		printf("%.3f/", roundtrip_min());
		printf("%.3f/", roundtrip_avg());
		printf("%.3f/", roundtrip_max());
		printf("%.3f", roundtrip_stddev());
		printf(" ms\n");
	}
	free_packets();
	ft_freeaddr();
	exit(0);
}
