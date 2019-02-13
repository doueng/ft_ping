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

static int	get_options(char *op_str)
{
	int options;

	options = 0;
	if (op_str[0] != '-')
		return (options);
	x(ft_strcmp(op_str, "-"), INVALID_OPTION);
	while (*++op_str)
	{
		if (*op_str == 'h')
			options |= H_OP;
		else if (*op_str == 'v')
			options |= V_OP;
		else
			return (x(-1, INVALID_OPTION));
	}
	return (options);
}


char		*get_ipstr(char *ipstr, void *addr)
{
	ipstr[INET_ADDRSTRLEN] = 0;
	inet_ntop(AF_INET,
			addr,
			ipstr,
			INET_ADDRSTRLEN);
	return (ipstr);
}

int	main(int argc, char *argv[])
{
	char	c;
	int		options;
	char	ipstr[INET_ADDRSTRLEN];

	ft_bzero(&g_env, sizeof(g_env));
	if (argc < 2)
		return (x(-1, USAGE));
	options = 0;
	if ((*++argv)[0] == '-')
		options = get_options(*argv++);
	if (options & H_OP)
		g_env.sweepinc = ft_atoi(*argv++);
	signal(SIGALRM, sig_alarm);
	signal(SIGINT, sig_term);
	create_env(*argv);
	ft_printf("PING %s (%s): %zu data bytes\n",
			*argv,
			get_ipstr(ipstr, &((struct sockaddr_in*)g_env.dst_addr)->sin_addr),
			g_env.data_size);
	main_loop();
	x(read(2, &c, 1), READ);
	return (0);
}
