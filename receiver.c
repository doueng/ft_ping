#include "ft_ping.h"

void	receiver(void)
{
	struct icmp		*icmp;
	int				ret;

	icmp = NULL;
	while (icmp == NULL)
	{
		ret = (recvmsg(g_env.sockfd, g_env.msg, 0));
		if (ret == -1 && errno == EWOULDBLOCK)
		{
			ft_printf("Request timeout for icmp_seq %d\n", g_env.icmp_send->icmp_seq);
			main_loop();
		}
		X(ret);
		icmp = g_env.icmp_recv;
		if (icmp->icmp_id == X(getpid()))
			break ;
	}
	g_env.packets_recv++;
}
