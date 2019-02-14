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


static void		update_icmp_send(struct icmp *icmp_send)
{
	ft_bzero(icmp_send, sizeof(*icmp_send));
	icmp_send->icmp_type = ICMP_ECHO;
	icmp_send->icmp_code = 0;
	icmp_send->icmp_id = x(getpid(), GETPID);
	icmp_send->icmp_seq = g_env.seq++;
	icmp_send->icmp_cksum = 0;
	icmp_send->icmp_cksum = checksum(icmp_send, sizeof(struct icmp));
}

void			sender(struct icmp *icmp_send)
{
	uint8_t	*packet;
	size_t	packet_size;

	update_icmp_send(icmp_send);
	g_env.data_size += g_env.sweepinc;
	packet_size = ICMP_SIZE + g_env.data_size;
	packet = (uint8_t*)xv(ft_memalloc(packet_size), MALLOC);
	ft_memcpy(packet, icmp_send, ICMP_SIZE);
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
