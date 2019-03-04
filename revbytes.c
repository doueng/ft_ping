/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revbytes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:49:16 by dengstra          #+#    #+#             */
/*   Updated: 2019/03/04 14:49:18 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

uint32_t	revbytes32(uint32_t bytes)
{
	return ((bytes << 24)
	| ((bytes << 8) & 0x00ff0000)
	| ((bytes >> 8) & 0x0000ff00)
	| (bytes >> 24));
}

uint16_t	revbytes16(uint16_t bytes)
{
	return ((bytes << 8) | (bytes >> 8));
}
