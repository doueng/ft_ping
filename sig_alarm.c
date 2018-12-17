#include "ft_ping.h"

void sig_alarm(int sigid)
{
	(void)sigid;
	dprintf(2, "timeout\n");
	exit(-1);
}
