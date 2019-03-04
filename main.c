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
	x(ft_strequ(op_str, "-") ? -1 : 0, USAGE);
	while (*++op_str)
	{
		*op_str == 'h' ? options |= H_OP : 0;
		*op_str == 'v' ? options |= V_OP : 0;
		*op_str == 't' ? options |= T_OP : 0;
		if (ft_strchr("hvt", *op_str) == NULL)
			x(-1, USAGE);
	}
	return (options);
}

static char	*parse_args(int argc, char *argv[])
{
	if (argc < 2)
		x(-1, USAGE);
	if ((*++argv)[0] == '-')
		g_env.options = get_options(*argv++);
	if (g_env.options & H_OP)
		x(-1, USAGE);
	if (g_env.options & T_OP && argc < 4)
		x(-1, USAGE);
	if (g_env.options & T_OP)
		g_env.ttl = ft_atoi(*argv++);
	return (*argv);
}

char		*get_ipstr(char *ipstr, void *addr)
{
	ft_bzero(ipstr, INET_ADDRSTRLEN + 1);
	inet_ntop(AF_INET,
			addr,
			ipstr,
			INET_ADDRSTRLEN);
	return (ipstr);
}

int			main(int argc, char *argv[])
{
	char	ipstr[INET_ADDRSTRLEN];
	char	c;
	char	*destination;

	if(getuid() != 0)
		x(-1, ROOT);
	ft_bzero(&g_env, sizeof(g_env));
	destination = parse_args(argc, argv);
	set_signals();
	create_env(destination);
	printf("PING %s (%s) %zu(%zu) bytes of data.\n",
			destination,
			get_ipstr(ipstr, &((struct sockaddr_in*)g_env.dst_addr)->sin_addr),
			g_env.data_size,
			g_env.data_size + ICMP_SIZE + sizeof(struct ip));
	main_loop();
	read(0, &c, 1);
	return (0);
}
