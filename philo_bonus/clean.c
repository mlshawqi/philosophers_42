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

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	if (array)
	{
		while (array[i])
		{
			if (array[i])
			{
				free(array[i]);
				array[i] = NULL;
			}
			i++;
		}
		free(array);
		array = NULL;
	}
}

void	free_list(t_philo **list)
{
	t_philo *p;

	
	if (list == NULL || *list == NULL)
		return ;
	while (*list != NULL)
	{
		p = (*list)->next;
		sem_close((*list)->meal_lock);
		sem_unlink((*list)->p_data->meals[(*list)->id -1]);
		sem_close((*list)->eat_count_lock);
		sem_unlink((*list)->p_data->eats[(*list)->id -1]);
		free(*list);
		*list = p;
	}
	free(*list);
	*list = NULL;
}

void    destroy_semaphores(t_data *data)
{
        int     i;

        i = 0;
	if(data->sem_array)
	{
		while(i < data->number_of_philosophers)
		{
			sem_close(data->sem_array[i]);
    			sem_unlink(data->names[i]);
			i++;
		}
		free(data->sem_array);
		sem_close(data->dead_lock);
		sem_unlink(DEAD_NAME);
		sem_close(data->print_lock);
		sem_unlink(PRINT_NAME);
	}
}

void    clean_up(t_data *data)
{
        if(data->philo)
                free_list(&data->philo);
	destroy_semaphores(data);
	if(data->names)
		free_string_array(data->names);
	if(data->meals)
		free_string_array(data->meals);
	if(data->eats)
		free_string_array(data->eats);
}