/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 12:10:33 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 12:10:33 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isnums(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && str[i] == '+' && ft_isdigit(str[i + 1]))
			i++;
		else if (ft_isdigit(str[i]) || ft_isspace(str[i]) || is_sign(str, i))
			i++;
		else
			return (0);
	}
	return (1);
}

static int	ft_valid(char *str)
{
	if (str[0] != '\0' && ft_isnums(str) && (ft_isempty(str) == 0))
		return (0);
	else
		return (1);
	return (0);
}

int	process_input(char **av, int ac)
{
	int	tmp;
	int	i;

	i = 1;
	while (i < ac)
	{
		tmp = ft_atoi(av[i]);
		if (tmp <= 0)
		{
			write(2, "Error: '", 8);
			write(2, av[i], ft_strlen(av[i]));
			print_error("' not a valid unsigned integer between 1 and INT_MAX",
				false);
			return (1);
		}
		i++;
	}
	return (0);
}

int	parsing(int ac, char *av[])
{
	int	i;

	if (ac == 5 || ac == 6)
	{
		i = 1;
		while (i < ac)
		{
			if (ft_valid(av[i]) != 0)
			{
				write(2, "Error: '", 8);
				write(2, av[i], ft_strlen(av[i]));
				print_error("' is not a valid unsigned integer.", false);
				return (1);
			}
			i++;
		}
		return (process_input(av, ac));
	}
	else
	{
		return (print_error("Usage: ./philo number_of_philosophers time_to_die "
				"time_to_eat time_to_sleep "
				"[number_of_times_each_philosopher_must_eat]", false));
	}
	return (0);
}
