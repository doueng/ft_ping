#include "ft_ping.h"

static struct icmp	*create_icmp(void)
{
	struct icmp	*icmp;

	icmp = (struct icmp*)Xv(ft_memalloc(sizeof(*icmp)));
	icmp->icmp_type = ICMP_ECHO;
	/* icmp->icmp_type = ICMP_TSTAMP; */
	icmp->icmp_code = 0;
	icmp->icmp_id = X(getpid());
	icmp->icmp_seq = 0;
	icmp->icmp_cksum = 0;
	icmp->icmp_cksum = checksum(icmp, sizeof(struct icmp));
	return (icmp);
}

static void 	create_msg(void)
{
	struct msghdr	*msg;
	struct iovec	*iov;
	uint8_t			*cbuf;
	size_t			size;

	size = sizeof(struct icmp) + sizeof(struct ip);
	msg = (struct msghdr*)Xv(ft_memalloc(sizeof(*msg)));
	cbuf = (uint8_t*)Xv(ft_memalloc(g_env.data_size));
	iov = (struct iovec*)Xv(ft_memalloc(sizeof(*iov)));
	iov->iov_base = (uint8_t*)Xv(ft_memalloc(size));
	iov->iov_len = size;

	msg->msg_name = NULL;
	msg->msg_namelen = 0;
	msg->msg_iov = iov;
	msg->msg_iovlen = 1;
	msg->msg_control = cbuf;
	msg->msg_controllen = sizeof(cbuf);
	msg->msg_flags = 0;
	g_env.msg = msg;
	g_env.ip = iov->iov_base;
	g_env.icmp_recv = (struct icmp*)(g_env.ip + 1);
}

static struct sockaddr	*get_sockaddr(char *address)
{
	struct addrinfo		hints;
	struct addrinfo 	*addrinfo;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_protocol = IPPROTO_ICMP;
	addrinfo = NULL;
	if (0 != getaddrinfo(address, NULL, &hints, &addrinfo))
	{
		ft_printf("ping: cannot resolve %s: Unknown host\n", address);
		exit(-1);
	}
	return (addrinfo->ai_addr);
}

static void				get_ipstr(t_env *env, struct sockaddr *addr)
{
	env->ipstr[INET_ADDRSTRLEN] = 0;
	inet_ntop(AF_INET,
			  &((struct sockaddr_in*)addr)->sin_addr,
			  env->ipstr,
			  INET_ADDRSTRLEN);
}

static void				set_timeouts(void)
{
	struct timeval timeout;


    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
	X(setsockopt (g_env.sockfd,
				  SOL_SOCKET, SO_RCVTIMEO,
				  (char *)&timeout,
				  sizeof(timeout)));
    /* X(setsockopt (g_env.sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, */
                /* sizeof(timeout))) */
}

void					create_env(char *address)
{
	g_env.dst_addr = get_sockaddr(address);
	g_env.data_size = 56;
	create_msg();
	g_env.sockfd = X(socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP));
	set_timeouts();
	get_ipstr(&g_env, g_env.dst_addr);
	g_env.icmp_send = create_icmp();
	g_env.address = address;
}
