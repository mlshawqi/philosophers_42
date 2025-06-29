/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 21:24:50 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 21:24:50 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *context, bool flag)
{
	if (flag)
	{
		write(2, "warning: failed to allocate ", 28);
		write(2, context, ft_strlen(context));
		write(2, "\n", 1);
	}
	else
	{
		write(2, context, ft_strlen(context));
		write(2, "\n", 1);
	}
	return (1);
}

char	*ft_strdup(char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = ft_strlen(s) + 1;
	dup = (char *)malloc(len * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len - 1)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	str = (char *)malloc((lens1 + lens2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcpy(str + lens1, s2);
	return (str);
}
