/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:00:17 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 12:00:24 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static char	*get_error_msg(int error)
{
	char *msg;

	msg = "ERROR";
	msg = error == READ ? "read failed" : msg;
	msg = error == RECV ? "recv failed" : msg;
	msg = error == GETPID ? "getpid failed" : msg;
	msg = error == SENDTO ? "sendto failed" : msg;
	msg = error == SETSOCK ? "setsock failed" : msg;
	msg = error == SOCKET ? "socket failed" : msg;
	msg = error == SIGNAL ? "signal failed" : msg;
	msg = error == INVALID_OPTION ? "Invaid option" : msg;
	msg = error == ROOT ? "ft_ping needs to be run as root" : msg;
	return (msg);
}

int			x(int res, int error)
{
	if (res == -1)
	{
		if (error != USAGE)
			fprintf(stderr, "Error: %s\n", get_error_msg(error));
		else
			fprintf(stderr, "Usage: ./ft_ping [-vh] [-t ttl] destination\n");
		exit(-1);
	}
	return (res);
}

void		*xv(void *res, int error)
{
	if (res == NULL)
	{
		fprintf(stderr, "Error: %s\n", get_error_msg(error));
		exit(-1);
	}
	return (res);
}
