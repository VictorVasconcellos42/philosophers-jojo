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
# include <sys/time.h>

typedef struct					s_philo
{
	int					seat;
	pthread_t			thread;
	pthread_mutex_t		mtx;
	int					dead;

	long unsigned			meals;
	int						full;
	long unsigned			last_meal;

	pthread_mutex_t			*left_hashi;	
	pthread_mutex_t			*right_hashi;

	struct s_table			*table;

} t_philo;

typedef struct s_table
{
	int				n_philos;
	t_philo				*philos;
	pthread_mutex_t			*hashis;
	pthread_t			monitor_thread;

	int				n_meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;

	long				start_time;
	int				end_simulation;


	int				philos_ready;

	pthread_mutex_t			mtx;
	pthread_mutex_t			write_mtx;

}						t_table;

// parser.c
int	ft_atol(char *ascii);
void parse(int argc, char **argv, t_table *table);

// utils.c
size_t	current_ms(void);

// dinner.c
int mise_en_place(t_table *table);

#endif
