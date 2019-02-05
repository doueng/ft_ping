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
	g_env.icmp_send->icmp_seq = g_env.seq++;
	g_env.icmp_send->icmp_cksum = 0;
	g_env.icmp_send->icmp_cksum = checksum(g_env.icmp_send, sizeof(struct icmp));
}

void	main_loop(void)
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
