#include "ft_ping.h"

void sig_alarm(int sigid)
{
	(void)sigid;
	/* ft_printf("Request timeout for icmp_seq %d\n", g_seq); */
	main_loop(&g_env);
}
