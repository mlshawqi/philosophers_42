/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 21:18:47 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 21:18:47 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	apply_initial_delay(t_philo *philo, int i, bool hint)
{
	if (hint)
	{
		if (i == 0 && philo->p_data->nbr_philos % 2 != 0 && philo->id == 1)
			ft_usleep(philo, (size_t)philo->p_data->t_eat);
		if (i == 0 && (philo->id % 2 != 0))
			ft_usleep(philo, (size_t)philo->p_data->t_eat);
	}
	else
	{
		if (philo->p_data->nbr_philos % 2 == 1
			&& philo->p_data->t_eat >= philo->p_data->t_sleep)
			ft_usleep(philo, 5);
	}
}

void	print_state(t_philo *philo, char *state)
{
	if (detect_death(philo))
		return ;
	sem_wait(philo->p_data->print_lock);
	if (!detect_death(philo))
		printf("%zu %d %s\n", get_current_time(philo), philo->id, state);
	sem_post(philo->p_data->print_lock);
}

void	pickup_forks(t_philo *philo)
{
	sem_wait(philo->p_data->forks);
	print_state(philo, "has taken a fork");
	sem_wait(philo->p_data->forks);
	print_state(philo, "has taken a fork");
}

void	putdown_forks(t_philo *philo)
{
	sem_post(philo->p_data->forks);
	sem_post(philo->p_data->forks);
}
