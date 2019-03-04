/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roundtrip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:00:50 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/14 16:00:52 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

float			roundtrip_min(void)
{
	float		min;
	t_packet	*curr;

	curr = g_env.packets;
	min = curr->triptime;
	while (curr)
	{
		min = min < curr->triptime ? min : curr->triptime;
		curr = curr->next;
	}
	return (min);
}

float			roundtrip_max(void)
{
	float		max;
	t_packet	*curr;

	curr = g_env.packets;
	max = curr->triptime;
	while (curr)
	{
		max = max > curr->triptime ? max : curr->triptime;
		curr = curr->next;
	}
	return (max);
}

float			roundtrip_avg(void)
{
	float		total;
	t_packet	*curr;

	curr = g_env.packets;
	total = 0;
	while (curr)
	{
		total += curr->triptime;
		curr = curr->next;
	}
	return (total / g_env.packets_recv);
}

float			roundtrip_stddev(void)
{
	float		avg;
	float		variance;
	t_packet	*curr;
	float		curr_variance;

	avg = roundtrip_avg();
	curr = g_env.packets;
	variance = 0;
	while (curr)
	{
		curr_variance = curr->triptime - avg;
		variance += curr_variance > 0 ? curr_variance : curr_variance * -1;
		curr = curr->next;
	}
	variance /= g_env.packets_recv;
	return(variance);
}

void			free_packets(void)
{
	t_packet *curr;
	t_packet *tmp;

	curr = g_env.packets;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
}
