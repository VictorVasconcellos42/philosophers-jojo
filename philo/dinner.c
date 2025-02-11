# include "philosophers.h"
void	*dinner(t_philo *philo);

int mise_en_place(t_table *table)
{
    int	count = 0;

    table->start_time = current_ms();
    while (count < table->n_philos)
    {
	pthread_create(&table->philos[count].thread, NULL, (void *)dinner, &table->philos[count]);
	count++;
    }
    count = 0;
    while (count < table->n_philos)
    {
	pthread_join(table->philos[count].thread, NULL);
	count++;
    }
    return (0);
}

int am_i_dead(t_philo *philo)
{
    if ((current_ms() - philo->last_meal) < (long unsigned)philo->table->time_to_eat)
	return (FALSE);
    return (TRUE);
}

void	print_action(char *str, t_philo *philo)
{
    pthread_mutex_lock(&philo->table->write_mtx);
    if (!am_i_dead(philo))
	printf("%lu %i %s\n", current_ms() - philo->table->start_time, philo->seat, str);
    pthread_mutex_unlock(&philo->table->write_mtx);
}

int eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_hashi);
    print_action("has taken a fork", philo);
    pthread_mutex_lock(philo->right_hashi);
    print_action("has taken a fork", philo);
    print_action("is eating", philo);
    pthread_mutex_unlock(philo->left_hashi);
    pthread_mutex_unlock(philo->right_hashi);
    return (0);
}

void	*dinner(t_philo *philo)
{
    eat(philo);
    // nap(philo);
    // think(philo);
    return (NULL);
}
