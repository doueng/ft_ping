#include "ft_ping.h"
#include <errno.h>
/* ssize_t */
/*      sendto(int socket, const void *buffer, size_t length, int flags, */
/*          const struct sockaddr *dest_addr, socklen_t dest_len); */
	/* struct sockaddr_in	servaddr; */

struct icmp	*create_icmp(void)
{
	struct icmp	*icmp;

	icmp = (struct icmp*)Xv(ft_memalloc(sizeof(*icmp)));
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_id = X(getpid());
	icmp->icmp_seq = 123;
	return (icmp);
}

struct sockaddr	*create_sockaddr(char *address)
{
	struct sockaddr_in *dstaddr;

	dstaddr = (struct sockaddr_in*)Xv(ft_memalloc(sizeof(struct sockaddr_in)));
	dstaddr->sin_family = AF_INET;
	X(inet_pton(AF_INET, address, &(dstaddr->sin_addr)));
	return ((struct sockaddr*)dstaddr);
}

void	sender(int sockfd, char *address)
{
	struct icmp			*icmp;
	struct sockaddr		*dstaddr;

	icmp = create_icmp();
	dstaddr = create_sockaddr(address);
	int sendto_ret = X(sendto(sockfd,
		   icmp,
		   sizeof(*icmp),
		   0,
		   dstaddr,
		   sizeof(struct sockaddr_in)));
	ft_printf("sendto size = %d\n", sendto_ret);
	free(icmp);
}

struct msghdr	*receiver(int sockfd)
{
	struct msghdr	*msg;
	struct iovec	*iov;
	uint8_t			*buf;
	uint8_t			*cbuf;

	msg = (struct msghdr*)Xv(ft_memalloc(sizeof(*msg)));
	buf = (uint8_t*)Xv(ft_memalloc(40));
	cbuf = (uint8_t*)Xv(ft_memalloc(40));
	iov = (struct iovec*)Xv(ft_memalloc(sizeof(*iov)));
	iov->iov_base = (void*)buf;
	iov->iov_len = 40;

	msg->msg_name = NULL;
	msg->msg_namelen = 0;
	msg->msg_iov = iov;
	msg->msg_iovlen = 1;
	msg->msg_control = cbuf;
	msg->msg_controllen = sizeof(cbuf);
	msg->msg_flags = 0;
	alarm(2);
	int recvmsg_size = X(recvmsg(sockfd, msg, 0));
	unsigned char *m = (unsigned char*)msg->msg_iov;
	ft_printf("recvmsg size = %d\n", recvmsg_size);
	for (int i = 0; i < msg->msg_iovlen; i++)
		printf(" %#1x ", *m++);
	/* ft_printf("iovlen = %d\n", msg.msg_iovlen); */
	return (msg);
}

int main(int argc, char *argv[])
{
	int					sockfd;

	if (argc != 2)
		return (-1);
	/* if (getuid() != 0) */
		/* return (ft_putstr("Need root\n")); */
	signal(SIGALRM, sig_alarm);
	sockfd = X(socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP));
	sender(sockfd, argv[1]);
	receiver(sockfd);
	X(close(sockfd));
	return (0);
}
