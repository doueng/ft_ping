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

uint16_t	revbytes16(uint16_t bytes)
{
	return ((bytes << 8) | (bytes >> 8));
}
