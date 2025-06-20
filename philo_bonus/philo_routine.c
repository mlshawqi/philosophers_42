/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 21:14:54 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 21:14:54 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_one_philo(t_philo *philo)
{
	sem_wait(philo->p_data->forks);
	print_state(philo, "has taken a fork");
	sem_post(philo->p_data->forks);
	ft_usleep(philo, (size_t)philo->p_data->time_to_die);
	sem_wait(philo->p_data->print_lock);
	printf("%zu %d died\n", get_current_time(philo), philo->id);
	sem_post(philo->p_data->print_lock);
}

void	philo_eat(t_philo *philo)
{
	if (detect_death(philo))
		return ;
	pickup_forks(philo);
	print_state(philo, "is eating");
	sem_wait(philo->meal_lock);
	philo->last_meal = get_current_time(philo);
	philo->eat_count += 1;
	philo->is_eating = true;
	sem_post(philo->meal_lock);
	ft_usleep(philo, (size_t)philo->p_data->t_eat);
	putdown_forks(philo);
	sem_wait(philo->meal_lock);
	philo->is_eating = false;
	sem_post(philo->meal_lock);
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

int	handle_monitor(t_philo *philo, bool create)
{
	if (create)
	{
		if (pthread_create(&philo->monitor, NULL, &monitor_routine, philo) != 0)
		{
			printf("Error creating monitor thread\n");
			return (1);
		}
	}
	else
	{
		if (pthread_join(philo->monitor, NULL) != 0)
		{
			printf("Error joing monitor thread\n");
			return (1);
		}
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	sem_wait(philo->meal_lock);
	philo->last_meal = get_current_time(philo);
	sem_post(philo->meal_lock);
	if (philo->p_data->nbr_philos == 1)
		handle_one_philo(philo);
	else
	{
		handle_monitor(philo, true);
		while (!detect_death(philo))
		{
			philo_think_sleep(philo, false);
			(apply_delay(philo, i, true), philo_eat(philo));
			if (should_stop_eating(philo, 0))
				break ;
			(philo_think_sleep(philo, true), apply_delay(philo, i, false));
			i++;
		}
		handle_monitor(philo, false);
	}
	return (NULL);
}
