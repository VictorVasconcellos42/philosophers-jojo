#include "philosophers.h"

void	init_hashis(t_table *table)
{
    table->hashis = malloc(sizeof(pthread_mutex_t) * (table->n_philos + 1));
    int	count = 0;
    while (count < table->n_philos)
    {
	pthread_mutex_init(&table->hashis[count], NULL);
	count++;
    }
}

void	init_philos(t_table *table)
{
    int	count = 0;

    table->philos = malloc(sizeof(t_philo) * table->n_philos + 1);
    while (count < table->n_philos)
    {
	table->philos[count].left_hashi = &table->hashis[count]; 
	if (count == table->n_philos - 1)
	    table->philos[count].right_hashi = &table->hashis[0];
	else
	    table->philos[count].right_hashi = &table->hashis[count + 1];
	table->philos[count].table = table;
	table->philos[count].meals = 0;
	table->philos[count].dead = 0;
	table->philos[count].last_meal = current_ms();
	table->philos[count].seat = count + 1;
	pthread_mutex_init(&table->philos[count].dead_mtx, NULL);
	count++;
    }
}

void	init(t_table *table)
{
    init_hashis(table);
    init_philos(table);
    table->start_time = current_ms();
    table->first_death = 0;
    table->philos_ready = 0;
    pthread_mutex_init(&table->dead_mtx, NULL);
    pthread_mutex_init(&table->write_mtx, NULL);
}

int main(int argc, char **argv)
{
    t_table table;

    if (argc < 5 || argc > 6)
    {
        printf("\ninsert a valid input(int):\n");
        printf("./philo number_of_philosophers time_to_die time_to_eat, time_to_sleep [number_of_times_each_philosopher_must_eat]\n\n");
        return (EXIT_FAILURE);
    }
    parse(argc, argv, &table);
    init(&table);
    mise_en_place(&table);
    return (EXIT_SUCCESS);
}
