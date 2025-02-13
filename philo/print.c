#include "philosophers.h"

void	printj(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_mtx);
	printf("%lu %i %s\n", current_ms() - philo->table->start_time, philo->seat,
			str);
	pthread_mutex_unlock(&philo->table->write_mtx);
}

int	print_routine(char *str, t_philo *philo)
{
	if (!death(philo))
		printj(str, philo);
	else
		return (1);
	return (0);
}
