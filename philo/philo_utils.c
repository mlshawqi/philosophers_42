/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 12:09:13 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 12:09:13 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->p_data->print_mutex);
	if (detect_death(philo))
	{
		pthread_mutex_unlock(&philo->p_data->print_mutex);
		return ;
	}
	printf("%zu %d %s\n", get_current_time(philo), philo->id, state);
	pthread_mutex_unlock(&philo->p_data->print_mutex);
}

void	increment_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_count_lock);
	philo->eat_count += 1;
	pthread_mutex_unlock(&philo->eat_count_lock);
}

void	pickup_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
	}
}

void	putdown_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

bool	finish_eating(t_philo *philo)
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
