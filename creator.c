/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:59:54 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 11:59:55 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static struct sockaddr	*get_sockaddr(char *address)
{
	struct addrinfo	hints;
	struct addrinfo	*addrinfo;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_protocol = IPPROTO_ICMP;
	addrinfo = NULL;
	if (0 != getaddrinfo(address, NULL, &hints, &addrinfo))
	{
		fprintf(stderr, "ping: cannot resolve %s: Unknown host\n", address);
		exit(-1);
	}
	return (addrinfo->ai_addr);
}

static void				set_sockopts(int sockfd)
{
	struct timeval	timeout;
	int				ttl;

	ft_bzero(&timeout, sizeof(timeout));
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	x(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout))
		, SETSOCK);
	ttl = 64;
	x(setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)), SETSOCK);
}

void					create_env(char *address)
{
	g_env.dst_addr = get_sockaddr(address);
	g_env.data_size = 56;
	g_env.sockfd = x(socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP), SOCKET);
	g_env.arg = address;
	set_sockopts(g_env.sockfd);
}
