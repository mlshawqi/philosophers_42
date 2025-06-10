#ifndef PHILO_H
# define PHILO_H


# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/wait.h>
#include <sys/time.h>

typedef struct  s_philo t_philo;
typedef struct  s_data  t_data;


typedef struct  s_philo{
        pthread_t       thread;
        pthread_mutex_t         *right_fork;
        pthread_mutex_t         *left_fork;
        int                     id;
        size_t                  last_eat;
        struct s_philo  *next;
        struct s_philo  *prev;
        t_data          *p_data;
}               t_philo;

typedef struct  s_data{
        t_philo         *philo;
        pthread_mutex_t *mutex_array;
        int             number_of_philosophers;
        size_t          time_to_die;
        int             time_to_eat;
        int             time_to_sleep;
        int             nb_to_eat;
        bool             dead_flag;
}       t_data;








// typedef struct  s_philo{
//         pthread_t       thread;
//         size_t     *lst_t_eat;
//         int     id;
//         pthread_mutex_t *r_fork_lock;
//         pthread_mutex_t *l_fork_lock;
//         pthread_mutex_t *dead_lock;
//         int     number_of_philosophers;
//         size_t     time_to_die;
//         int     time_to_eat;
//         int     time_to_sleep;
//         int     nb_to_eat;
//         int     *dead_flag;
//         int     is_eat;
//         int     is_sleep;
//         bool    is_stoop;
//         size_t  **array_l_time;
// }               t_philo;

// typedef struct  s_data{
//         t_philo *philo;
//         pthread_mutex_t *mutex_array;
//         size_t     *last_eat_array;
//         pthread_mutex_t d_lock;
//         int     number_of_philosophers;
//         size_t     time_to_die;
//         int     time_to_eat;
//         int     time_to_sleep;
//         int     nb_to_eat;
//         int     flag_die;
//         bool    is_stoop;
// }       t_data;

int    parsing(int ac, char *av[], t_data *data);
int    process_input(char **av, int ac, t_data *data);
int    ft_initialize(char **av, int ac, t_data *data);
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
int    init_data(t_data *data);
int	link_node(t_philo **head, t_philo *new_node);
t_philo         *creat_node(t_data *data, int i);
void    cleanup_data(t_data *data);
void	clean_philo(t_philo **list);
int	print_error(char *context, bool flag);
size_t	ft_strlen(char *s);
void	init_fork(t_data *data);
int    simulation(t_data *data);

#endif