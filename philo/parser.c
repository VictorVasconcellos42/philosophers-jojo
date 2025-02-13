#include "philosophers.h"

static void	is_nbr(char **argv)
{
    int	n = 1;
    int	i;

    while (argv && argv[n])
    {
	i = 0;
	while (argv[n][i] && argv[n][i] >= '0' && argv[n][i] <= '9')
	    i++;
	if (argv[n][i] != '\0')
	{
	    printf("\ninput must be a positive int\n");
	    exit (1);
	}
	n++;
    }
}

void parse(int argc, char **argv, t_table *table)
{
    int ret = 0;

    is_nbr(argv);
    table->n_philos = ft_atol(argv[1]);
    if (table->n_philos > 200 || table->n_philos < 1)
	    ret = printf("number of philosophers must be from 1 to 200\n");
    table->time_to_die = ft_atol(argv[2]);
    if (table->time_to_die > INT_MAX || table->time_to_die < 1)
	    ret = printf("time to die must be from 1 to %i\n", INT_MAX);
    table->time_to_eat = ft_atol(argv[3]);
    if (table->time_to_eat > INT_MAX || table->time_to_eat < 1)
	    ret = printf("time to die must be from 1 to %i\n", INT_MAX);
    table->time_to_sleep = ft_atol(argv[4]);
    if (table->time_to_sleep > INT_MAX || table->time_to_sleep < 1)
	    ret = printf("time to die must be from 1 to %i\n", INT_MAX);
    if (argc == 6)
    {
	table->n_meals = ft_atol(argv[5]);
	    if (table->n_meals > INT_MAX || table->n_meals < 0)
		ret = printf("number of times each philosopher must eat has be from 0 to %i\n", INT_MAX);
    }
    else
	table->n_meals = -1;
    if (ret)
	exit (1);
}
