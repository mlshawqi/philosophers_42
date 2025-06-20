/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 21:06:33 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 21:06:33 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	detect_death(t_philo *philo)
{
	bool	ret;

	ret = false;
	sem_wait(philo->p_data->dead_lock);
	if (philo->p_data->dead_flag)
		ret = true;
	sem_post(philo->p_data->dead_lock);
	return (ret);
}

bool	should_stop_eating(t_philo *philo, int eat_counter)
{
	int		counter;

	(void)eat_counter;
	if (philo->p_data->nb_to_eat <= 0)
		return (false);
	sem_wait(philo->meal_lock);
	counter = philo->eat_count;
	sem_post(philo->meal_lock);
	if (counter >= philo->p_data->nb_to_eat)
	{
		return (true);
	}
	return (false);
}

bool	simulation_stop(t_philo *tmp)
{
	size_t	meals;
	bool	is_eating;
	int		eat_counter;

	if (detect_death(tmp))
		return (true);
	sem_wait(tmp->meal_lock);
	meals = tmp->last_meal;
	is_eating = tmp->is_eating;
	eat_counter = tmp->eat_count;
	sem_post(tmp->meal_lock);
	if (!is_eating && should_stop_eating(tmp, eat_counter))
		return (true);
	if (!is_eating && ((get_current_time(tmp)
				- meals) > tmp->p_data->time_to_die))
	{
		sem_wait(tmp->p_data->dead_lock);
		tmp->p_data->dead_flag = true;
		sem_wait(tmp->p_data->print_lock);
		printf("%zu %d died\n", get_current_time(tmp), tmp->id);
		sem_post(tmp->p_data->print_lock);
		exit(1);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!detect_death(philo))
	{
		if (simulation_stop(philo))
		{
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
