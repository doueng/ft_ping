#include "ft_ping.h"

static struct msghdr	*create_msg(void)
{
	struct msghdr	*msg;
	struct iovec	*iov;
	/* uint8_t			*cbuf; */
	size_t			size;

	size = sizeof(struct icmp) + sizeof(struct ip);
	msg = (struct msghdr*)Xv(ft_memalloc(sizeof(*msg)));
	/* cbuf = (uint8_t*)Xv(ft_memalloc(40)); */
	iov = (struct iovec*)Xv(ft_memalloc(sizeof(*iov)));
	iov->iov_base = (uint8_t*)Xv(ft_memalloc(size));
	iov->iov_len = size;

	msg->msg_name = NULL;
	msg->msg_namelen = 0;
	msg->msg_iov = iov;
	msg->msg_iovlen = 1;
	/* msg->msg_control = cbuf; */
	/* msg->msg_controllen = sizeof(cbuf); */
	msg->msg_flags = 0;
	return (msg);
}

void	printer(t_env *env, struct icmp *icmp, struct ip *ip, double triptime)
{
	printf("%zu bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
		   env->data_size + 8,
		   env->ipstr,
		   icmp->icmp_seq,
		   ip->ip_ttl,
		   (triptime / 1000.0));
}

void	main_loop(t_env *env)
{
	struct timeval	send_time;
	struct timeval	recv_time;
	struct ip		*ip;
	struct icmp		*icmp;
	struct msghdr	*msg;

	msg = create_msg();
	ip = msg->msg_iov->iov_base;
	icmp = (struct icmp*)(ip + 1);
	while (1)
	{

		gettimeofday(&send_time, NULL);
		sender(env);
		ft_printf("sentd\n");
		alarm(1);
		receiver(env->sockfd, msg);
		ft_printf("recv\n");
		gettimeofday(&recv_time, NULL);
		alarm(0);
		int usecs = recv_time.tv_usec - send_time.tv_usec;
		int secs = recv_time.tv_sec - send_time.tv_sec;
		/* triptime = tv.tv_sec * 10000 + (tv.tv_usec / 100); */
		/* printer(env, icmp, ip, (secs * 1000 + (usecs / 100.0))); */
		printer(env, icmp, ip, (recv_time.tv_usec - send_time.tv_usec));
		/* free(icmp); */
		env->icmp->icmp_seq = ++g_env.seq;
		env->icmp->icmp_cksum = 0;
		env->icmp->icmp_cksum = checksum(env->icmp, sizeof(struct icmp));
		sleep(1);
	}
	// free msg
}
