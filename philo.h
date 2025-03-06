#ifndef PHILO_H
# define PHILO_H


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/wait.h>
#include <sys/time.h>


typedef struct  s_philo{
        pthread_t       thread;
        size_t     *lst_t_eat;
        int     id;
        pthread_mutex_t *r_fork_lock;
        pthread_mutex_t *l_fork_lock;
        pthread_mutex_t *dead_lock;
        int     number_of_philosophers;
        size_t     time_to_die;
        int     time_to_eat;
        int     time_to_sleep;
        int     nb_to_eat;
        int     *dead_flag;
        int     is_eat;
        int     is_sleep;
        size_t  **array_l_time;
}               t_philo;


typedef struct  s_data{
        t_philo *philo;
        pthread_mutex_t *mutex_array;
        size_t     *last_eat_array;
        pthread_mutex_t d_lock;
        int     number_of_philosophers;
        size_t     time_to_die;
        int     time_to_eat;
        int     time_to_sleep;
        int     nb_to_eat;
        int     flag_die;
}       t_data;

void    parsing(int ac, char *av[], t_data *data);
void    process_input(char **av, int ac, t_data *data);
void    ft_initialize(int *arr, int ac, t_data *data);
int     ft_isdigit(char *str);
int     ft_atoi(char *str);

void    ft_to_mutex(t_data *data);
size_t	get_current_time(void);
int	ft_usleep(size_t milliseconds);

int    to_threads(t_data *data);
size_t    manage_l_time(size_t **array, int len);
void    *routine(void *arg);
void    manage_exit(size_t *array, int len);
int     check_dead(t_philo *philo);


#endif