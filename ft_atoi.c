#include "philo.h"

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
        if (str[i] == '-' || str[i] == '+')
        {
                if (str[i] == '-')
                        sign *= -1;
                i++;
        }
        while (str[i] >= '0' && str[i] <= '9')
        {
                if (result > 2147483647)
                        return (-1);
                result *= 10;
                result += str[i] - 48;
                i++;
        }
        return (result * sign);
}
