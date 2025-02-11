#include "philosophers.h"

size_t	current_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep2(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = current_ms();
	while ((current_ms() - start) < milliseconds)
	{
		print_action("rodou loop", philo);
		usleep(5);
	}
	print_action("saiu loop", philo);
	return (0);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = current_ms();
	while ((current_ms() - start) < milliseconds)
		usleep(500);
	return (0);
}
