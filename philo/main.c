/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 12:06:28 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 12:06:28 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (parsing(argc, argv) == 1)
		return (1);
	if (ft_initialize(argv, argc, &data) == 1)
	{
		clean_up(&data);
		return (1);
	}
	if (simulation(&data) == 1)
	{
		clean_up(&data);
		return (1);
	}
	clean_up(&data);
	return (0);
}
