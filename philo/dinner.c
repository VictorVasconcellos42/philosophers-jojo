# include "philosophers.h"

static int more_meals(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->meal_mtx);
    if (philo->table->n_meals == -1 || philo->meals < philo->table->n_meals)
    {
	pthread_mutex_unlock(&philo->table->meal_mtx);
	return (TRUE);
    }
    pthread_mutex_unlock(&philo->table->meal_mtx);
    return (FALSE);
}

static int eat(t_philo *philo)
{
    if (!more_meals(philo))
	return (1);
    pthread_mutex_lock(philo->left_hashi);
    if (print_routine("has taken a fork", philo) == 1)
	return (1);
    pthread_mutex_lock(philo->right_hashi);
    if (print_routine("has taken a fork", philo) == 1)
	return (1);
    if (print_routine("is eating", philo) == 1)
	return (1);
    philo->last_meal = current_ms();
    if (usleep_until(philo->table->time_to_eat, philo) == 1)
	return (1);
    pthread_mutex_unlock(philo->left_hashi);
    pthread_mutex_unlock(philo->right_hashi);
    philo->meals++;
    return (0);
}

static int nap(t_philo *philo)
{
    if (print_routine("is sleeping", philo) == 1)
	return (1);
    if (usleep_until(philo->table->time_to_sleep, philo))
	return (1);
    return (0);
}

static int think(t_philo *philo)
{
    if (print_routine("is thinking", philo) == 1)
	return (1);
    return (0);
}

void	*dinner(t_philo *philo)
{
    while (1)
	if (philo->table->philos_ready)
	    break ;
    philo->table->start_time = current_ms();
    philo->last_meal = philo->table->start_time;
    if (philo->seat % 2 == 0)
	usleep(100);
    while (!death(philo))
    {
	if (eat(philo) == 1)
	    break ;
	if (nap(philo) == 1)
	    break ;
	if (think(philo) == 1)
	    break ;
    }
    printf("%i\n", philo->seat);
    return (NULL);
}
