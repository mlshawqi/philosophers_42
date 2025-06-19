/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 12:17:48 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 12:17:48 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *s)
{
	size_t	j;

	j = 0;
	while (s[j] != '\0')
		j++;
	return (j);
}

t_philo	*creat_node(t_data *data, int i)
{
	t_philo	*node;

	node = malloc(sizeof(t_philo));
	if (!node)
		return (NULL);
	node->id = i;
	node->p_data = data;
	node->last_meal = 0;
	node->eat_count = 0;
	node->is_eating = false;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	link_node(t_philo **head, t_philo *new_node)
{
	t_philo	*current;

	if (!new_node)
		return (print_error("philo_node", true));
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
	return (0);
}
