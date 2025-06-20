/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 21:12:00 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 21:12:00 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	if (array)
	{
		while (array[i])
		{
			if (array[i])
			{
				free(array[i]);
				array[i] = NULL;
			}
			i++;
		}
		free(array);
		array = NULL;
	}
}

void	close_sem(sem_t **sem)
{
	if (sem && *sem != SEM_FAILED && *sem != NULL)
	{
		sem_close(*sem);
		*sem = NULL;
	}
}

void	free_list(t_philo **list, bool hint)
{
	t_philo	*p;

	if (list == NULL || *list == NULL)
		return ;
	while (*list != NULL)
	{
		p = (*list)->next;
		if (hint)
			sem_unlink((*list)->p_data->meals[(*list)->id - 1]);
		close_sem(&(*list)->meal_lock);
		free(*list);
		*list = p;
	}
	if (*list)
		free(*list);
	*list = NULL;
}

void	destroy_semaphores(t_data *data)
{
	close_sem(&data->dead_lock);
	sem_unlink("/dead");
	close_sem(&data->print_lock);
	sem_unlink("/print");
	close_sem(&data->forks);
	sem_unlink("/forks");
	close_sem(&data->time_lock);
	sem_unlink("/time");
}

void	clean_up(t_data *data, bool hint)
{
	if (hint)
	{
		if (data->philo)
			free_list(&data->philo, true);
		destroy_semaphores(data);
		if (data->meals)
			free_string_array(data->meals);
		if (data->eats)
			free_string_array(data->eats);
	}
	else
	{
		close_sem(&data->dead_lock);
		close_sem(&data->print_lock);
		close_sem(&data->forks);
		close_sem(&data->time_lock);
		if (data->philo)
			free_list(&data->philo, false);
		if (data->meals)
			free_string_array(data->meals);
		if (data->eats)
			free_string_array(data->eats);
	}
}
