#include "philosophers.h"

size_t	current_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = current_ms();
	while ((current_ms() - start) < milliseconds)
		usleep(50);
	return (0);
}

int	usleep_until(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = current_ms();
	while ((current_ms() - start) < milliseconds)
	{
		if (death(philo))
			return (1);
		usleep(50);
	}
	return (0);
}

int atoi_wrapper(char *ascii);

int	ft_atol(char *ascii)
{
	int	i;
	int	sig;
	int	count;
	long	nb;

	i = 0;
	sig = 1;
	count = 1;
	nb = 0;
	while ((ascii[i] >= 8 && ascii[i] <= 13) || (ascii[i] == ' '))
		i++;
	while ((ascii[i] == '-' || ascii[i] == '+') && count--)
	{
		if (ascii[i] == '-')
			sig = -1;
		i++;
	}
	while (ascii[i] >= '0' && ascii[i] <= '9')
		nb = nb * 10 + (ascii[i++] - '0');
    return (nb * sig);
}
