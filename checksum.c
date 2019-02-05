#include "ft_ping.h"

uint16_t	checksum(void *b, int len)
{
	uint16_t	*buf;
	uint32_t	sum;

	buf = b;
	sum = 0;
	while (len > 1)
	{
		sum += *buf++;
		len -= 2;
	}
	if (len == 1)
		sum += *(uint8_t*)buf;
	while (sum >> 16)
           sum = (sum & 0xffff) + (sum >> 16);
	return (~sum);
}
