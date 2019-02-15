#include "ft_ping.h"

uint16_t	revbytes16(uint16_t bytes)
{
	return ((bytes << 8) | (bytes >> 8));
}
