#include "ft_ping.h"

static struct icmp	*create_icmp(void)
{
	struct icmp	*icmp;

	icmp = (struct icmp*)Xv(ft_memalloc(sizeof(*icmp)));
	icmp->icmp_type = ICMP_ECHO;
	/* icmp->icmp_type = ICMP_TSTAMP; */
	icmp->icmp_code = 0;
	icmp->icmp_id = X(getpid());
	icmp->icmp_seq = g_seq;
	icmp->icmp_cksum = 0;
	icmp->icmp_cksum = checksum(icmp, sizeof(struct icmp));
	return (icmp);
}

/* static struct sockaddr	*create_sockaddr(char *address) */
/* { */
/* 	struct sockaddr_in *dstaddr; */

/* 	dstaddr = (struct sockaddr_in*)Xv(ft_memalloc(sizeof(struct sockaddr_in))); */
/* 	dstaddr->sin_family = AF_INET; */
/* 	X(inet_pton(AF_INET, address, &(dstaddr->sin_addr))); // error 0 and -1 */
/* 	return ((struct sockaddr*)dstaddr); */
/* } */

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
	/* while (addrinfo) */
		/* addrinfo = addrinfo->ai_next; */
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

t_env			*create_env(char *address)
{
	/* t_env *env; */

	ft_bzero(&g_env, sizeof(g_env));
	/* g_env = (t_env*)Xv(malloc(sizeof(*env))); */
	g_env.dst_addr = get_sockaddr(address);
	g_env.sockfd = X(socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP));
	get_ipstr(&g_env, g_env.dst_addr);
	g_env.icmp = create_icmp();
	g_env.data_size = 56;
	g_env.address = address;
	return (&g_env);
}
