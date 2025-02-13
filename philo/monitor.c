# include "philosophers.h"

static int mark_dead(t_philo *philo)
{
    if ((current_ms() - philo->last_meal) < (long unsigned)philo->table->time_to_die)
	return (FALSE);
    pthread_mutex_lock(&philo->table->dead_mtx);
    if (!philo->table->death)
	philo->table->death = philo->seat;
    pthread_mutex_unlock(&philo->table->dead_mtx);
    return (TRUE);
}

int death(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->dead_mtx);
    if (philo->table->death)
    {
	pthread_mutex_unlock(&philo->table->dead_mtx);
	return (TRUE);
    }
    pthread_mutex_unlock(&philo->table->dead_mtx);
    return (FALSE);
}

void	*monitor(t_table *table)
{
    int	philos_eaten = 0;
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
	    // exit (1);
	    // return (NULL);
	    // end simulation and destroy threads
	    break ;
	}
	else if (!more_meals(&table->philos[count]))
	{
	    philos_eaten++;
	    if (philos_eaten == table->n_philos)
		break ;
	}

	count++;
	if (count == table->n_philos)
	    count = 0;
    }
    return (NULL);
}
