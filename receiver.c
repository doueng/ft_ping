/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:00:06 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 12:00:07 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	receiver(void)
{
	struct icmp		*icmp;
	int				ret;

	icmp = NULL;
	while (icmp == NULL)
	{
		ret = (recvmsg(g_env.sockfd, g_env.msg, 0));
		if (ret == -1 && errno == EWOULDBLOCK)
		{
			ft_printf("Request timeout for icmp_seq %d\n",
					g_env.icmp_send->icmp_seq);
			main_loop();
		}
		x(ret, RECV);
		icmp = g_env.icmp_recv;
		if (icmp->icmp_id == x(getpid(), GETPID))
			break ;
	}
	g_env.packets_recv++;
}
