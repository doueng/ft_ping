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

void			sig_term(int sigid)
{
	if (sigid != SIGINT)
		return ;
	printf("--- %s ping statistics ---\n", g_env.arg);
	printf(
		"%zu packets transmitted, %zu packets received, %.1f%% packet loss\n",
		g_env.packets_sent,
		g_env.packets_recv,
		calc_packet_loss(g_env.packets_sent, g_env.packets_recv));
	printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
		roundtrip_min(),
		roundtrip_avg(),
		roundtrip_max(),
		roundtrip_stddev());
	exit(0);
}
