#include "ft_ping.h"

void sig_alarm(int sigid)
{
	if (sigid != SIGALRM)
		return ;
	main_loop();
}

static double	calc_packet_loss(double pkt_sent, double pkt_recv)
{
	// divide by zero
	return (((pkt_sent - pkt_recv) / pkt_sent) * 100);
}

void sig_term(int sigid)
{
	if (sigid != SIGINT)
		return ;
	printf("%zu packets transmitted, %zu packets received, %.1f%% packet loss\n",
			g_env.packets_sent,
			g_env.packets_recv,
			calc_packet_loss(g_env.packets_sent, g_env.packets_recv));
	exit(0);
}
