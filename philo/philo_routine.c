/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 12:06:07 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 12:06:07 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a r fork");
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_eat(t_philo *philo)
{
	if (detect_death(philo))
		return ;
	pickup_forks(philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_current_time(philo);
	philo->is_eating = true;
	pthread_mutex_unlock(&philo->meal_lock);
	print_state(philo, "is eating");
	increment_eat_count(philo);
	ft_usleep(philo, (size_t)philo->p_data->t_eat);
	pthread_mutex_lock(&philo->meal_lock);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->meal_lock);
	putdown_forks(philo);
}

void	philo_think_sleep(t_philo *philo, bool hint)
{
	if (hint)
	{
		if (detect_death(philo))
			return ;
		print_state(philo, "is sleeping");
		ft_usleep(philo, (size_t)philo->p_data->t_sleep);
	}
	else
	{
		print_state(philo, "is thinking");
	}
}

void	apply_initial_delay(t_philo *philo, int i, bool hint)
{
	if (hint)
	{
		if (i == 0 && philo->p_data->nbr_philos % 2 != 0 && philo->id == 1)
			ft_usleep(philo, (size_t)philo->p_data->t_eat);
		if (i == 0 && (philo->id % 2 != 0))
			ft_usleep(philo, (size_t)(philo->p_data->t_eat / 2));
	}
	else
	{
		if (philo->p_data->nbr_philos % 2 == 1
			&& philo->p_data->t_eat >= philo->p_data->t_sleep)
			ft_usleep(philo, 5);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_current_time(philo);
	pthread_mutex_unlock(&philo->meal_lock);
	if (philo->p_data->nbr_philos == 1)
		handle_one_philo(philo);
	else
	{
		while (!detect_death(philo))
		{
			philo_think_sleep(philo, false);
			apply_initial_delay(philo, i, true);
			philo_eat(philo);
			philo_think_sleep(philo, true);
			apply_initial_delay(philo, i, false);
			i++;
		}
	}
	return (NULL);
}
