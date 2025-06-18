#include "philo.h"

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

int    ft_initialize(char **av, int ac, t_data *data)
{
        data->philo = NULL;
        data->mutex_array = NULL;
        data->time_to_die = (size_t)ft_atoi(av[2]);
        data->time_to_eat = ft_atoi(av[3]);
        data->time_to_sleep = ft_atoi(av[4]);
        data->dead_flag = false;
        data->nb_to_eat = 0;
        data->number_of_philosophers = ft_atoi(av[1]);
        if(data->number_of_philosophers > 200 || data->number_of_philosophers <= 0)
        {
                write(2, "Error: '", 8);
                write(2, av[1], ft_strlen(av[1]));
                print_error("' there must be between 1 and 200 philosophers.", false);
                return (1);
        }
        if(ac == 6)
        {
                data->nb_to_eat = ft_atoi(av[5]);
                if(data->nb_to_eat == 0)
                        data->dead_flag = true;
        }
        if(init_data(data) == 1)
                return (1);
        return (0);
}
