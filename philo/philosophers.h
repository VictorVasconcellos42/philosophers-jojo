#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#define TRUE 1
#define FALSE 0

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct					s_philo
{
	int					id;
	pthread_t			thread_id;
	pthread_mutex_t				mtx;

	long				meals_count;
	bool				full;
	long				last_meal_time;

	pthread_mutex_t     *left_hashi;
	pthread_mutex_t		*right_hashi;

	struct s_table				*table;

} t_philo;

typedef struct s_table
{
	int					n_philos;
    t_philo				*philos;
	pthread_mutex_t		*hashis;
	pthread_t			monitor_thread;

	int					n_meals;
	int					time_to_die;
	int					time_to_eat;
	int				time_to_sleep;

	long				start_time;
	bool				end_simulation;


	bool				all_philos_ready;
	long				philos_ready;

	pthread_mutex_t				table_mtx;
	pthread_mutex_t				write_mtx;

}						t_table;

// parser.c
int	ft_atol(char *ascii);
void parse(int argc, char **argv, t_table *table);

#endif
