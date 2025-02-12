# include "philosophers.h"
void	*dinner(t_philo *philo);
void	*monitor(t_table *table);

int mise_en_place(t_table *table)
{
    int	count = 0;

    pthread_create(&table->monitor_thread, NULL, (void *)monitor, table);
    while (count < table->n_philos)
    {
	pthread_create(&table->philos[count].thread, NULL, (void *)dinner, &table->philos[count]);
	count++;
    }
    table->philos_ready = 1;
    count = 0;
    pthread_join(table->monitor_thread, NULL);
    while (count < table->n_philos)
    {
	pthread_join(table->philos[count].thread, NULL);
	count++;
    }
    return (0);
}

int eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_hashi);
    print_routine("has taken a fork", philo);
    pthread_mutex_lock(philo->right_hashi);
    print_routine("has taken a fork", philo);
    print_routine("is eating", philo);
    philo->last_meal = current_ms();
    usleep_until(philo->table->time_to_eat, philo);
    pthread_mutex_unlock(philo->left_hashi);
    pthread_mutex_unlock(philo->right_hashi);
    philo->meals++;
    return (0);
}

int nap(t_philo *philo)
{
    print_routine("is sleeping", philo);
    usleep_until(philo->table->time_to_sleep, philo);
    return (0);
}

int think(t_philo *philo)
{
    print_routine("is thinking", philo);
    return (0);
}

void	*dinner(t_philo *philo)
{
	//    while (1)
	// if (philo->table->philos_ready)
	//     break ;
    philo->table->start_time = current_ms();
    philo->last_meal = philo->table->start_time;
    if (philo->seat % 2 == 0)
	usleep(15000);
    while (!check_death(philo))
    {
	if (eat(philo) == 1)
	    break ;
	if (nap(philo) == 1)
	    break ;
	if (think(philo) == 1)
	    break ;
    }
    return (NULL);
}
