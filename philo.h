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
        pthread_mutex_t         meal_lock;
        pthread_mutex_t         eat_count_lock;
        bool                    done;
        int                     id;
        size_t                  last_meal;
        int                     eat_count;
        struct s_philo  *next;
        struct s_philo  *prev;
        t_data          *p_data;
}               t_philo;

typedef struct  s_data{
        t_philo         *philo;
        pthread_t       monitor;
        pthread_mutex_t *mutex_array;
        pthread_mutex_t dead_lock;
        pthread_mutex_t print_mutex;
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

int    parsing(int ac, char *av[]);
int    process_input(char **av, int ac);
int    ft_initialize(char **av, int ac, t_data *data);
int	ft_isdigit(int c);
int     ft_atoi(char *str);
int	ft_isspace(int c);
int	ft_isdigit(int c);
int	ft_isspace(int c);
int	ft_isempty(char *str);
int	is_sign(char *str, int i);
int	ft_isnums(char *str);

void    ft_to_mutex(t_data *data);
size_t	get_current_time(void);
int	ft_usleep(size_t wait_time);

int    to_threads(t_data *data);
size_t    manage_l_time(size_t **array, int len);
void    *philo_routine(void *arg);
void    manage_exit(size_t *array, int len);
int     check_dead(t_philo *philo);
int    init_data(t_data *data);
int	link_node(t_philo **head, t_philo *new_node);
t_philo         *creat_node(t_data *data, int i);
void    clean_up(t_data *data);
void	clean_philo(t_philo **list);
int	print_error(char *context, bool flag);
size_t	ft_strlen(char *s);
void	init_fork(t_data *data);
int    simulation(t_data *data);
void     *monitor_routine(void *arg);

#endif