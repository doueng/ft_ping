#include "ft_ping.h"

void	sender(t_env *env)
{
	struct icmp			*icmp;
	uint8_t				*packet;
	size_t				packet_size;

	icmp = env->icmp;
	packet_size = sizeof(*icmp) + env->data_size;
	packet = Xv(ft_memalloc(packet_size));
	ft_memcpy(packet, icmp, sizeof(*icmp));
	X(sendto(
		  env->sockfd,
		  packet,
		  packet_size,
		  0,
		  env->dst_addr,
		  sizeof(struct sockaddr_in)));
	free(packet);
}
