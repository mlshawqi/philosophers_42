#include "philo.h"

int     ft_isdigit(char *str)
{
        int     i;

        i = 0;
        while (str[i] != '\0')
        {
                if (str[i] >= '0' && str[i] <= '9')
                        i++;
                else
                        return (1);
        }
        return (0);
}

void    ft_initialize(int *arr, int ac, t_data *data)
{
        data->number_of_philosophers = arr[0];
        data->time_to_die = arr[1];
        data->time_to_eat = arr[2];
        data->time_to_sleep = arr[3];
        if(ac == 6)
                data->nb_to_eat = arr[4];
}

void    process_input(char **av, int ac, t_data *data)
{
        int     i;
        int     j;
        int     *arr;

        arr = NULL;
        arr = malloc(sizeof(int) * ac);
        if(!arr)
                exit(1);
        i = 1;
        j = 0;
        while(i < ac)
        {
                arr[j] = ft_atoi(av[i]);
                if(arr[j] == -1 || (arr[0] == 0 || arr[0] > 200))
                {
                        free(arr);
                        printf("Error: arg '%s' must be between 0 and INT_MAX,", av[i]);
                        printf(" or 1 to 200 for number_of_philosophers.\n");
                        exit(1);  
                }
                i++;
                j++;
        }
        ft_initialize(arr, ac, data);
        free(arr);
}

void    parsing(int ac, char *av[], t_data *data)
{
        int     i;

        if (ac == 5 || ac == 6)
        {
                i = 1;
                while (i < ac)
                {
                        if (av[i][0] != '\0' && ft_isdigit(av[i]) == 0)
                                i++;
                        else
                        {
                                printf("Error: arg '%s' is not a valid unsigned integer.\n", av[i]);
                                exit(1);
                        }
                }
                process_input(av, ac, data);
        }
        else
        {
                printf("Usage: ./philo number_of_philosophers time_to_die");
                printf("time_to_eat time_to_sleep");
                printf("[number_of_times_each_philosopher_must_eat]\n");
                exit(1);
        }
}
