# include "philosophers.h"
void	*dinner(t_philo *philo);
void	*monitor(t_table *table);

int mise_en_place(t_table *table)
{
    int	count = 0;

    table->start_time = current_ms();
    
    pthread_create(&table->monitor_thread, NULL, (void *)monitor, table);
    while (count < table->n_philos)
    {
	pthread_create(&table->philos[count].thread, NULL, (void *)dinner, &table->philos[count]);
	count++;
    }
    count = 0;

    pthread_join(table->monitor_thread, NULL);
    while (count < table->n_philos)
    {
	pthread_join(table->philos[count].thread, NULL);
	count++;
    }
    table->philos_ready = 1;
    return (0);
}

int dead(t_philo *philo)
{
    if ((current_ms() - philo->last_meal) < (long unsigned)philo->table->time_to_die)
	return (FALSE);
    pthread_mutex_lock(&philo->table->dead_mtx);
    if (philo->table->first_death)
    {
	// destroy(philo->table);
	exit (1);
	pthread_mutex_unlock(&philo->table->dead_mtx);
    }
    philo->table->first_death = 1;
    pthread_mutex_unlock(&philo->table->dead_mtx);
    return (TRUE);
}

void	print_action(char *str, t_philo *philo)
{
    pthread_mutex_lock(&philo->table->write_mtx);
    if (!dead(philo))
	printf("%lu %i %s\n", current_ms() - philo->table->start_time, philo->seat, str);
    else
	printf("%lu %i is DEAD\n", current_ms() - philo->table->start_time, philo->seat);
    pthread_mutex_unlock(&philo->table->write_mtx);
}

// void	print_as_monitor(char *str, t_philo *philo)
// {
//     pthread_mutex_lock(&philo->table->write_mtx);
//     if (am_i_dead(philo))
// 	printf("%lu %i %s\n", current_ms() - philo->table->start_time, philo->seat, str);
//     pthread_mutex_unlock(&philo->table->write_mtx);
// }

int eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_hashi);
    print_action("has taken a fork", philo);
    pthread_mutex_lock(philo->right_hashi);
    print_action("has taken a fork", philo);
    print_action("is eating", philo);
    ft_usleep(philo->table->time_to_eat);
    philo->last_meal = current_ms();
    pthread_mutex_unlock(philo->left_hashi);
    pthread_mutex_unlock(philo->right_hashi);
    philo->meals++;
    return (0);
}

int nap(t_philo *philo)
{
    print_action("is sleeping", philo);
    ft_usleep(philo->table->time_to_sleep);
    return (0);
}

int think(t_philo *philo)
{
    print_action("is thinking", philo);
    ft_usleep(philo->table->time_to_think);
    return (0);
}

void	*monitor(t_table *table)
{
    int	count = 0;

    while (count < table->n_philos)
    {
	pthread_mutex_lock(&table->dead_mtx);
	if (table->philos[count].dead)
	{
	    pthread_mutex_unlock(&table->dead_mtx);
	    // end simulation and destroy threads
	    break ;
	}
	pthread_mutex_unlock(&table->dead_mtx);
	count++;
	if (count == table->n_philos)
	    count = 0;
    }
    return (NULL);
}

void	*dinner(t_philo *philo)
{
    if (philo->seat % 2 == 0)
	ft_usleep(1);
    while (!dead(philo))
    {
	eat(philo);
	nap(philo);
	think(philo);
    }
    return (NULL);
}
