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

int eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_hashi);
    printf("%lu %i has taken a fork\n", current_ms() - philo->table->start_time, philo->id);
    pthread_mutex_lock(philo->right_hashi);
    printf("%lu %i has taken a fork\n", current_ms() - philo->table->start_time, philo->id);
    printf("%lu %i is eating\n", current_ms() - philo->table->start_time, philo->id);
    pthread_mutex_unlock(philo->left_hashi);
    pthread_mutex_unlock(philo->right_hashi);
    return (0);
}

void	*dinner(t_philo *philo)
{
    //eat
    eat(philo);
    //sleep
    // sleep(philo);
    //think
    // think(philo);
    return (NULL);
}
