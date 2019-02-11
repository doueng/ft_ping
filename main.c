/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:59:58 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 11:59:59 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_env g_env;

int	main(int argc, char *argv[])
{
	char c;

	if (argc != 2)
		return (-1);
	ft_bzero(&g_env, sizeof(g_env));
	signal(SIGALRM, sig_alarm);
	signal(SIGINT, sig_term);
	create_env(argv[1]);
	ft_printf("PING %s (%s): %zu data bytes\n",
			argv[1],
			g_env.ipstr,
			g_env.data_size);
	main_loop();
	x(read(2, &c, 1), READ);
	return (0);
}
