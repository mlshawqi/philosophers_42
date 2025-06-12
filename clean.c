#include "philo.h"

void	free_list(t_philo **list)
{
	t_philo *p;

	
	if (list == NULL || *list == NULL)
		return ;
	while (*list != NULL)
	{
		p = (*list)->next;
                pthread_mutex_destroy(&(*list)->meal_lock);
		free(*list);
		*list = p;
	}
	free(*list);
	*list = NULL;
}

void    destroy_mutex(t_data *data)
{
        int     i;

        i = 0;
        while(i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->mutex_array[i]);
		i++;
	}
        free(data->mutex_array);
        pthread_mutex_destroy(&data->dead_lock);
        pthread_mutex_destroy(&data->print_mutex);
}

void    clean_up(t_data *data)
{
        if(data->philo)
                free_list(&data->philo);
        destroy_mutex(data);
}