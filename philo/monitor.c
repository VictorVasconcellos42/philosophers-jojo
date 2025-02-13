# include "philosophers.h"

int mark_dead(t_philo *philo)
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

void	printj(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_mtx);
	printf("%lu %i %s\n", current_ms() - philo->table->start_time, philo->seat, str);
	pthread_mutex_unlock(&philo->table->write_mtx);
}

void	print_routine(char *str, t_philo *philo)
{
    if (!death(philo))
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
			printj("is DEAD", &table->philos[count]);
			break ;
		}
		else if (table->n_meals != -1 && table->philos[count].meals == table->n_meals)
			break ;
		count++;
		if (count == table->n_philos)
			count = 0;
    }
    return (NULL);
}
