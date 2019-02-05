#include "ft_ping.h"

t_env g_env;

int main(int argc, char *argv[])
{
	char c;

	if (argc != 2)
		return (-1);
	ft_bzero(&g_env, sizeof(g_env));
	/* if (getuid() != 0) */
	/* 	return (ft_putstr("Need root\n")); */
	signal(SIGALRM, sig_alarm);
	signal(SIGINT, sig_term);
	create_env(argv[1]);
	ft_printf("PING %s (%s): %zu data bytes\n",
			  argv[1],
			  g_env.ipstr,
			  g_env.data_size);
	main_loop();
	read(2, &c, 1);
	return (0);
}
