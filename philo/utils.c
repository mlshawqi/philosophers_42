#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

int	ft_isempty(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

int	is_sign(char *str, int i)
{
	if (ft_isspace(str[i - 1]) && str[i] == '+' && ft_isdigit(str[i + 1]))
		return (1);
	return (0);
}

int     ft_atoi(char *str)
{
        long    result;
        int             sign;
        int             i;

        result = 0;
        sign = 1;
        i = 0;
        while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
                i++;
        if (str[i] == '+')
                i++;
        while (str[i] >= '0' && str[i] <= '9')
        {
                if (result > 2147483647)
                        return (-1);
                result *= 10;
                result += str[i] - 48;
                i++;
        }
        while(str[i] != '\0' && ft_isspace(str[i]))
                        i++;
        if(str[i] != '\0')
                return (-1);
        return (result * sign);
}
