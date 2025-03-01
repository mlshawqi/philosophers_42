#ifndef PHILO_H
# define PHILO_H


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/wait.h>
#include <sys/time.h>



typedef struct  s_data{
        pthread_t *philo;
        int     number_of_philosophers;
        int     time_to_die;
        int     time_to_eat;
        int     time_to_sleep;
        int     nb_to_eat;
}       t_data;

void    parsing(int ac, char *av[], t_data *data);
void    process_input(char **av, int ac, t_data *data);
void    ft_initialize(int *arr, int ac, t_data *data);
int     ft_isdigit(char *str);
int     ft_atoi(char *str);

#endif