#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define TRUE 1
# define FALSE 0

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				seat;
	pthread_t		thread;
	// pthread_mutex_t		dead_mtx;

	// int					dead;

	int				meals;
	// int						full;
	long unsigned	last_meal;

	pthread_mutex_t	*left_hashi;
	pthread_mutex_t	*right_hashi;

	struct s_table	*table;

}					t_philo;

typedef struct s_table
{
	int				n_philos;
	t_philo			*philos;
	pthread_mutex_t	*hashis;
	pthread_t		monitor_thread;

	int				n_meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;

	int				philos_ready;

	long			start_time;

	int				death;
	pthread_mutex_t	dead_mtx;
	pthread_mutex_t	meal_mtx;

	pthread_mutex_t	write_mtx;

}					t_table;

// dinner.c
void				*dinner(t_philo *philo);
int					more_meals(t_philo *philo);

// init.c
void				init(t_table *table);

// monitor.c
int					death(t_philo *philo);
void				*monitor(t_table *table);

// parser.c
void				parse(int argc, char **argv, t_table *table);

// utils.c
size_t				current_ms(void);
int					ft_usleep(size_t milliseconds);
int					usleep_until(size_t milliseconds, t_philo *philo);
int					ft_atol(char *ascii);

// print.c
void				printj(char *str, t_philo *philo);
int					print_routine(char *str, t_philo *philo);

#endif
