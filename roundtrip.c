#include "ft_ping.h"

float			roundtrip_min(void)
{
	float		min;
	t_packet 	*curr;

	curr = g_env.packets;
	min = curr->triptime;
	while (curr)
	{
		min = min < curr->triptime ? min : curr->triptime;
		curr = curr->next;
	}
	return (min / 1000);
}

float			roundtrip_max(void)
{
	float		max;
	t_packet 	*curr;

	curr = g_env.packets;
	max = curr->triptime;
	while (curr)
	{
		max = max > curr->triptime ? max : curr->triptime;
		curr = curr->next;
	}
	return (max / 1000);
}

float			roundtrip_avg(void)
{
	float		total;
	t_packet 	*curr;

	curr = g_env.packets;
	total = 0;
	while (curr)
	{
		total += curr->triptime;
		curr = curr->next;
	}
	return (total / g_env.packets_recv / 1000);
}

float			roundtrip_stddev(void)
{
	float		avg;
	float		variance;
	t_packet 	*curr;

	avg = roundtrip_avg() * 1000;
	curr = g_env.packets;
	variance = 0;
	while (curr)
	{
		variance += (curr->triptime - avg) * (curr->triptime - avg);
		curr = curr->next;
	}
	variance /= g_env.packets_recv;
	return (ft_sqrt_float(variance) / 1000);
}
