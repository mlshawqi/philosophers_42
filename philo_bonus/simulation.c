/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 21:12:34 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 21:12:34 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data_sem(t_data *data)
{
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->nbr_philos);
	if (data->forks == SEM_FAILED)
		return (print_error("sem_open forks_lock failed", false));
	sem_unlink("/dead");
	data->dead_lock = sem_open("/dead", O_CREAT | O_EXCL, 0644, 1);
	if (data->dead_lock == SEM_FAILED)
		return (print_error("sem_open dead_lock failed", false));
	sem_unlink("/print");
	data->print_lock = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	if (data->print_lock == SEM_FAILED)
		return (print_error("sem_open print_lock failed", false));
	sem_unlink("/time");
	data->time_lock = sem_open("/time", O_CREAT | O_EXCL, 0644, 1);
	if (data->time_lock == SEM_FAILED)
		return (print_error("sem_open time_lock failed", false));
	return (0);
}

int	init_child_sem(t_philo *philo)
{
	sem_unlink(philo->p_data->meals[philo->id - 1]);
	philo->meal_lock = sem_open(philo->p_data->meals[philo->id - 1],
			O_CREAT | O_EXCL, 0644, 1);
	if (philo->meal_lock == SEM_FAILED)
		return (print_error("sem_open meal_lock failed", false));
	return (0);
}

int	creat_processes(t_data *data)
{
	t_philo	*tmp;

	tmp = data->philo;
	if (init_data_sem(data) != 0)
		return (1);
	while (tmp)
	{
		tmp->pid = fork();
		if (tmp->pid < 0)
			return (print_error("error fork philo child", false));
		if (tmp->pid == 0)
		{
			init_child_sem(tmp);
			philo_routine(tmp);
			clean_up(data, false);
			exit(0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	wait_processes(t_data *data)
{
	t_philo	*tmp;
	int		status;

	tmp = data->philo;
	while (tmp)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && (WEXITSTATUS(status) != 0))
		{
			kill_all_philos(tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	simulation(t_data *data)
{
	if (creat_processes(data) == 1)
		return (1);
	if (wait_processes(data) == 1)
		return (1);
	return (0);
}
