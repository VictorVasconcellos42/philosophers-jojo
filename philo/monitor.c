# include "philosophers.h"

int mark_dead(t_philo *philo)
{
    if ((current_ms() - philo->last_meal) < (long unsigned)philo->table->time_to_die)
	return (FALSE);
    pthread_mutex_lock(&philo->dead_mtx);
    if (philo->dead)
	philo->dead = 1;
    pthread_mutex_unlock(&philo->dead_mtx);
    return (TRUE);
}

int check_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->dead_mtx);
    if (philo->dead)
    {
	pthread_mutex_unlock(&philo->dead_mtx);
	return (TRUE);
    }
    pthread_mutex_unlock(&philo->dead_mtx);
    return (FALSE);
}

void	printj(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_mtx);
	printf("%lu %i %s\n", current_ms() - philo->table->start_time, philo->seat, str);
	pthread_mutex_unlock(&philo->table->write_mtx);
}

void	print_routine(char *str, t_philo *philo)
{
    if (check_death(philo))
    {
	printj("is DEAD", philo);
	exit (1);
    }
    printj(str, philo);
}

void	*monitor(t_table *table)
{
    int	count = 0;

    while (1)
	if (table->philos_ready)
	    break ;
    while (count < table->n_philos)
    {
	if (mark_dead(&table->philos[count]))
	{
	    // printf("%lu, \n", current_ms() - table->philos[count].last_meal);
	    printj("is DEAD", &table->philos[count]);
	    exit (1);
	    // end simulation and destroy threads
	    break ;
	}
	count++;
	if (count == table->n_philos)
	    count = 0;
    }
    return (NULL);
}
