#include "ft_ping.h"

struct msghdr	*receiver(int sockfd, struct msghdr	*msg)
{
	struct icmp		*icmp;

	icmp = NULL;
	while (icmp == NULL)
	{
		X(recvmsg(sockfd, msg, 0));
		icmp = msg->msg_iov->iov_base + sizeof(struct ip);
		if (icmp->icmp_id == X(getpid()))
			break ;
	}

	/* icmp = Xv(malloc(sizeof(*icmp))); */
	/* ft_memcpy(icmp, msg->msg_iov->iov_base + sizeof(struct ip), sizeof(*icmp)); */
	/* ft_printf("ttl %d\n", ((struct ip*)msg->msg_iov->iov_base)->ip_ttl); */
	/* free(msg->msg_iov->iov_base); */
	/* free(msg->msg_iov); */
	/* free(msg); */
	return (msg);
}
