/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 21:22:38 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 21:22:38 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(t_philo *philo)
{
	static struct timeval	start_time;
	static int				start;
	struct timeval			current_time;
	long					seconds;
	long					microseconds;

	sem_wait(philo->p_data->time_lock);
	if (!start)
	{
		if (gettimeofday(&start_time, NULL) == -1)
			return (print_error("gettimeofday() error\n", NULL));
		start = 1;
	}
	sem_post(philo->p_data->time_lock);
	if (gettimeofday(&current_time, NULL) == -1)
		return (print_error("gettimeofday() error\n", NULL));
	seconds = current_time.tv_sec - start_time.tv_sec;
	microseconds = current_time.tv_usec - start_time.tv_usec;
	return ((seconds * 1000) + (microseconds / 1000));
}

int	ft_usleep(t_philo *philo, size_t wait_time)
{
	size_t	start_time;

	if (detect_death(philo))
		return (1);
	start_time = get_current_time(philo);
	while (!detect_death(philo) && ((get_current_time(philo)
				- start_time) < wait_time))
		usleep(500);
	return (0);
}
