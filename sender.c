#include "ft_ping.h"

void	sender(void)
{
	struct icmp			*icmp;
	uint8_t				*packet;
	size_t				packet_size;

	icmp = g_env.icmp_send;
	packet_size = sizeof(*icmp) + g_env.data_size;
	packet = Xv(ft_memalloc(packet_size));
	ft_memcpy(packet, icmp, sizeof(*icmp));
	X(sendto(
		  g_env.sockfd,
		  packet,
		  packet_size,
		  0,
		  g_env.dst_addr,
		  sizeof(struct sockaddr_in)));
	g_env.packets_sent++;
	free(packet);
}
