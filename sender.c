/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:00:09 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 12:00:10 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	sender(void)
{
	struct icmp			*icmp;
	uint8_t				*packet;
	size_t				packet_size;

	icmp = g_env.icmp_send;
	packet_size = sizeof(*icmp) + g_env.data_size;
	packet = (uint8_t*)xv(ft_memalloc(packet_size), MALLOC);
	ft_memcpy(packet, icmp, sizeof(*icmp));
	x(sendto(
		g_env.sockfd,
		packet,
		packet_size,
		0,
		g_env.dst_addr,
		sizeof(struct sockaddr_in))
		, SENDTO);
	g_env.packets_sent++;
	free(packet);
}
