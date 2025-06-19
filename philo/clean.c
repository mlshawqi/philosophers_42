#include "philo.h"

int	print_error(char *context, bool flag)
{
	if (flag)
	{
		write(2, "warning: failed to allocate ", 28);
		write(2, context, ft_strlen(context));
		write(2, "\n", 1);
	}
	else
	{
		write(2, context, ft_strlen(context));
		write(2, "\n", 1);
	}
	return (1);
}

void	free_list(t_philo **list)
{
	t_philo *p;

	
	if (list == NULL || *list == NULL)
		return ;
	while (*list != NULL)
	{
		p = (*list)->next;
                pthread_mutex_destroy(&(*list)->meal_lock);
		pthread_mutex_destroy(&(*list)->eat_count_lock);
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
	if(data->mutex_array)
	{
		while(i < data->nbr_philos)
		{
			pthread_mutex_destroy(&data->mutex_array[i]);
			i++;
		}
		free(data->mutex_array);
		pthread_mutex_destroy(&data->dead_lock);
		pthread_mutex_destroy(&data->print_mutex);
	}
}

void    clean_up(t_data *data)
{
        if(data->philo)
                free_list(&data->philo);
        destroy_mutex(data);
}