#include "../includes/wolf3d.h"

void	error(char *str)
{
	printf("error: %s\n", str);
	exit(-1);
}

int		main(int argc, char **argv)
{
	t_env env;

	if (argc != 1)
	{
		printf("Usage: %s\n", argv[0]);
		return (-1);
	}
	prepare_level(&env, 1);
	create_the_environment(&env);
	return (0);
}
