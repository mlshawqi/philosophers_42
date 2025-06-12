#include "philo.h"

t_philo         *creat_node(t_data *data, int i)
{
	t_philo         *node;

	node = malloc(sizeof(t_philo));
	if (!node)
		return (NULL);
        node->id = i;
	node->p_data = data;
	node->last_meal = 0;
	node->nb_eat = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	link_node(t_philo **head, t_philo *new_node)
{
	t_philo	*current;

        if (!new_node)
		return (print_error("philo_node", true));
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
	return (0);
}

void	init_fork(t_data *data)
{
	int	i;
	t_philo		*tmp;

	i = 0;
	tmp = data->philo;
	while(i < data->number_of_philosophers)
	{
		if(!tmp->prev)
			tmp->left_fork = &data->mutex_array[data->number_of_philosophers - 1];
		tmp->right_fork = &data->mutex_array[i];
		if(tmp->next)
			tmp->next->left_fork = &data->mutex_array[i];
		i++;
		tmp = tmp->next;
	}
}

int    init_data(t_data *data)
{
        int     i;

	i = 0;
	data->mutex_array = malloc(data->number_of_philosophers * sizeof(pthread_mutex_t));
        if(!data->mutex_array)
		return (print_error("mutex_array", true));
	while(i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->mutex_array[i], NULL);
		i++;
	}
	i = 0;
        while(i < data->number_of_philosophers)
        {
                if(link_node(&data->philo, creat_node(data, i + 1)) == 1)
			return (1);
                i++;
        }
	init_fork(data);
	return (0);
}

size_t	ft_strlen(char *s)
{
	size_t	j;

	j = 0;
	while (s[j] != '\0')
		j++;
	return (j);
}

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