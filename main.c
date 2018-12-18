#include "ft_ping.h"

uint16_t g_seq = 0;

int main(int argc, char *argv[])
{
	t_env				*env;

	if (argc != 2)
		return (-1);
	/* if (getuid() != 0) */
	/* 	return (ft_putstr("Need root\n")); */
	signal(SIGALRM, sig_alarm);
	create_env(argv[1]);
	ft_printf("PING %s (%s): %zu data bytes\n",
			  argv[1],
			  env->ipstr,
			  env->data_size);
	main_loop(env);
	free(env);
	return (0);
}
