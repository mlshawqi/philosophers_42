/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 12:09:45 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 12:09:45 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	detect_death(t_philo *philo)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&philo->p_data->dead_lock);
	if (philo->p_data->dead_flag)
		ret = true;
	pthread_mutex_unlock(&philo->p_data->dead_lock);
	return (ret);
}

bool	should_stop_eating(t_philo *philo)
{
	bool	ret;

	ret = false;
	if (philo->p_data->nb_to_eat <= 0)
		return (false);
	pthread_mutex_lock(&philo->eat_count_lock);
	if (philo->eat_count >= philo->p_data->nb_to_eat)
		ret = true;
	pthread_mutex_unlock(&philo->eat_count_lock);
	return (ret);
}

bool	all_philos_done(t_philo *philo)
{
	while (philo)
	{
		if (should_stop_eating(philo))
			philo = philo->next;
		else
			return (false);
	}
	return (true);
}

bool	simulation_stop(t_data *data, t_philo *tmp)
{
	size_t	meals;
	bool	is_eating;

	pthread_mutex_lock(&tmp->meal_lock);
	meals = tmp->last_meal;
	is_eating = tmp->is_eating;
	pthread_mutex_unlock(&tmp->meal_lock);
	if (!is_eating && ((get_current_time(tmp) - meals) > data->time_to_die))
	{
		pthread_mutex_lock(&data->dead_lock);
		data->dead_flag = true;
		pthread_mutex_unlock(&data->dead_lock);
		pthread_mutex_lock(&data->print_mutex);
		printf("%zu %d died\n", get_current_time(tmp), tmp->id);
		pthread_mutex_unlock(&data->print_mutex);
		return (true);
	}
	else if (all_philos_done(data->philo))
	{
		pthread_mutex_lock(&data->dead_lock);
		data->dead_flag = true;
		pthread_mutex_unlock(&data->dead_lock);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	t_philo	*tmp;

	data = (t_data *)arg;
	while (!detect_death(data->philo))
	{
		tmp = data->philo;
		while (tmp)
		{
			if (simulation_stop(data, tmp))
				return (NULL);
			tmp = tmp->next;
		}
		usleep(500);
	}
	return (NULL);
}
