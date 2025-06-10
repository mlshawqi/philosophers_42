#include "philo.h"

t_philo         *creat_node(int i)
{
	t_philo         *node;

	node = malloc(sizeof(t_philo));
	if (!node)
		return (NULL);
        node->id = i;
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

int    init_data(t_data *data)
{
        int     i;

	data->mutex_array = malloc(data->number_of_philosophers * sizeof(pthread_mutex_t));
        if(!data->mutex_array)
		return (print_error("mutex_array", true));
        i = 0;
        while(i < data->number_of_philosophers)
        {
                if(link_node(&data->philo, creat_node(i + 1)) == 1)
			return (1);
                i++;
        }
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