/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 21:10:44 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 21:10:44 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*gave_name(char *str, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*name;

	tmp = NULL;
	tmp2 = NULL;
	name = NULL;
	tmp = ft_itoa(i);
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin("/", str);
	if (!tmp2)
	{
		free(tmp);
		return (NULL);
	}
	name = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	if (!name)
		return (NULL);
	return (name);
}

char	**get_names(t_data *data, char *name)
{
	int		i;
	char	**names;

	names = NULL;
	names = malloc(sizeof(char *) * (data->nbr_philos + 1));
	if (!names)
	{
		print_error("array of names", true);
		return (NULL);
	}
	i = 0;
	ft_bzero(names, (data->nbr_philos + 1) * sizeof(char *));
	while (i < data->nbr_philos)
	{
		names[i] = gave_name(name, i);
		if (!names[i])
		{
			free_string_array(names);
			print_error("data_names", true);
			return (NULL);
		}
		i++;
	}
	return (names);
}

int	init_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		if (link_node(&data->philo, creat_node(data, i + 1)) == 1)
			return (1);
		i++;
	}
	data->meals = get_names(data, "meals");
	data->eats = get_names(data, "eat");
	if (!data->meals || !data->eats)
		return (1);
	return (0);
}

int	ft_initialize(char **av, int ac, t_data *data)
{
	data->philo = NULL;
	data->meals = NULL;
	data->eats = NULL;
	data->print_lock = NULL;
	data->dead_lock = NULL;
	data->time_lock = NULL;
	data->forks = NULL;
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
		data->nb_to_eat = ft_atoi(av[5]);
	if (init_data(data) == 1)
		return (1);
	return (0);
}
