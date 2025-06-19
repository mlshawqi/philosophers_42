/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 12:12:40 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 12:12:40 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork(t_data *data)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = data->philo;
	while (i < data->nbr_philos)
	{
		if (!tmp->prev)
			tmp->left_fork = &data->mutex_array[data->nbr_philos - 1];
		tmp->right_fork = &data->mutex_array[i];
		if (tmp->next)
			tmp->next->left_fork = &data->mutex_array[i];
		i++;
		tmp = tmp->next;
	}
}

int	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->mutex_array = malloc(data->nbr_philos * sizeof(pthread_mutex_t));
	if (!data->mutex_array)
		return (print_error("mutex_array", true));
	while (i < data->nbr_philos)
	{
		pthread_mutex_init(&data->mutex_array[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nbr_philos)
	{
		if (link_node(&data->philo, creat_node(data, i + 1)) == 1)
			return (1);
		i++;
	}
	init_fork(data);
	return (0);
}

int	ft_initialize(char **av, int ac, t_data *data)
{
	data->philo = NULL;
	data->mutex_array = NULL;
	data->time_to_die = (size_t)ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->dead_flag = false;
	data->nb_to_eat = 0;
	data->nbr_philos = ft_atoi(av[1]);
	if (data->nbr_philos > 200 || data->nbr_philos <= 0)
	{
		write(2, "Error: '", 8);
		write(2, av[1], ft_strlen(av[1]));
		print_error("' there must be between 1 and 200 philosophers.", false);
		return (1);
	}
	if (ac == 6)
	{
		data->nb_to_eat = ft_atoi(av[5]);
		if (data->nb_to_eat == 0)
			data->dead_flag = true;
	}
	if (init_data(data) == 1)
		return (1);
	return (0);
}
