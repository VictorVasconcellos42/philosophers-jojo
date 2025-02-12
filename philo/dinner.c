# include "philosophers.h"
#include <pthread.h>
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
    // mutext
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

int mark_dead(t_philo *philo)
{
    if ((current_ms() - philo->last_meal) < (long unsigned)philo->table->time_to_die + 20)
	return (FALSE);
	//    if (philo->last_meal == 0)
	//    {
	// return FALSE;
	//    }
    pthread_mutex_lock(&philo->dead_mtx);
    if (philo->dead)
    {
	pthread_mutex_unlock(&philo->dead_mtx);
	return (TRUE);
    }
    philo->dead = philo->seat;
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

int am_i_dead(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->dead_mtx);
    if (philo->table->first_death == philo->seat)
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

void	print_action(char *str, t_philo *philo)
{
    if (check_death(philo))
    {
	printj(str, philo);
	exit (1);
    }
    printj(str, philo);
}

int eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_hashi);
    print_action("has taken a fork", philo);
    pthread_mutex_lock(philo->right_hashi);
    print_action("has taken a fork", philo);
    print_action("is eating", philo);
    philo->last_meal = current_ms();
    usleep_until(philo->table->time_to_eat, philo);
    pthread_mutex_unlock(philo->left_hashi);
    pthread_mutex_unlock(philo->right_hashi);
    philo->meals++;
    return (0);
}

int nap(t_philo *philo)
{
    print_action("is sleeping", philo);
    usleep_until(philo->table->time_to_sleep, philo);
    return (0);
}

int think(t_philo *philo)
{
    print_action("is thinking", philo);
    return (0);
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
	    print_action("is DEAD", &table->philos[count]);
	    // end simulation and destroy threads
	    break ;
	}
	count++;
	if (count == table->n_philos)
	    count = 0;
    }
    return (NULL);
}

void	*dinner(t_philo *philo)
{
    while (1)
	if (philo->table->philos_ready)
	    break ;
    if (philo->seat % 2 == 0)
	usleep(15000);
    while (!check_death(philo))
    {
	eat(philo);
	nap(philo);
	think(philo);
    }
    return (NULL);
}
