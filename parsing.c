#include "philo.h"

int     ft_isdigit(char *str)
{
        int     i;

        i = 0;
        if(!str || str[i] == '\0')
                return (1);
        if(str[i] == '+' && str[i + 1] != '\0')
                i++;
        while (str[i] != '\0')
        {
                if (str[i] >= '0' && str[i] <= '9')
                        i++;
                else
                        return (1);
        }
        return (0);
}

int    ft_initialize(char **av, int ac, t_data *data)
{
        data->philo = NULL;
        data->number_of_philosophers = ft_atoi(av[1]);
        if(data->number_of_philosophers > 200 || data->number_of_philosophers == 0)
        {
                write(2, "Error: '", 8);
                write(2, av[1], ft_strlen(av[1]));
                print_error("' there must be between 1 and 200 philosophers.", false);
                return (1);
        }
        data->time_to_die = ft_atoi(av[2]);
        data->time_to_eat = ft_atoi(av[3]);
        data->time_to_sleep = ft_atoi(av[4]);
        data->dead_flag = false;
        if(ac == 6)
        {
                data->nb_to_eat = ft_atoi(av[5]);
                if(data->nb_to_eat == 0)
                        data->dead_flag = true;
        }
        if(init_data(data) == 1)
                return (1);
        return (0);
}

int    process_input(char **av, int ac, t_data *data)
{
        int     tmp;
        int     i;

        i = 1;
        while(i < ac)
        {
                tmp = ft_atoi(av[i]);
                if(tmp == -1)
                {
                        write(2, "Error: '", 8);
                        write(2, av[i], ft_strlen(av[i]));
                        print_error("' not a valid unsigned integer between 0 and INT_MAX", false);
                        return (1);
                }
                i++;
        }
        if(ft_initialize(av, ac, data) == 1)
                return (1);
        return (0);
}

int    parsing(int ac, char *av[], t_data *data)
{
        int     i;

        if (ac == 5 || ac == 6)
        {
                i = 1;
                while (i < ac)
                {
                        if (ft_isdigit(av[i]) != 0)
                        {
                                write(2, "Error: '", 8);
                                write(2, av[i], ft_strlen(av[i]));
                                print_error("' is not a valid unsigned integer.", false);
                                return (1);
                        }
                        i++;
                }
                return(process_input(av, ac, data));
        }
        else
        {
                return (print_error("Usage: ./philo number_of_philosophers time_to_die "
                "time_to_eat time_to_sleep "
                "[number_of_times_each_philosopher_must_eat]", false));
        }
        return (0);
}
