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
#include <semaphore.h>
#include <fcntl.h>
# include <signal.h>

#define SEM_FAIL ((sem_t *) -1)

typedef struct  s_philo t_philo;
typedef struct  s_data  t_data;


typedef struct  s_philo{
        pthread_t       monitor;
        sem_t           *meal_lock;
        sem_t           *eat_count_lock;
        int                     id;
        pid_t                   pid;
        size_t                  last_meal;
        int                     eat_count;
        struct s_philo  *next;
        struct s_philo  *prev;
        t_data          *p_data;
}               t_philo;

typedef struct  s_data{
        t_philo         *philo;
        sem_t           *forks;
        sem_t           *dead_lock;
        sem_t           *print_lock;
        char            **meals;
        char            **eats;
        int             number_of_philosophers;
        size_t          time_to_die;
        int             time_to_eat;
        int             time_to_sleep;
        int             nb_to_eat;
        bool             dead_flag;
}       t_data;







// #define SEM_FAIL ((sem_t *) -1)
// #define DEAD_NAME "/dead"
// #define EATEN_COUNTER "/eaten_counter"
// #define PRINT_NAME "/print"
// #define FORKS_NAME "/forks"


// typedef struct  s_philo t_philo;
// typedef struct  s_data  t_data;


// typedef struct  s_philo{
//         pthread_t       monitor;
//         pid_t             pid;
//         sem_t           *fork;
//         sem_t         *right_fork;
//         sem_t         *left_fork;
//         sem_t         *meal_lock;
//         sem_t         *eat_count_lock;
//         sem_t           *print;
//         sem_t           *counter;
//         int                     id;
//         size_t                  last_meal;
//         int                     eat_count;
//         struct s_philo  *next;
//         struct s_philo  *prev;
//         t_data          *p_data;
// }               t_philo;

// typedef struct  s_data{
//         t_philo         *philo;
//         pid_t             pid;
//         sem_t          *forks;
//         char    **names;
//         char    **meals;
//         char    **eats;
//         sem_t   **sem_array;
//         sem_t *dead_lock;
//         sem_t *print_lock;
//         sem_t   *eat_counter;
//         int             number_of_philosophers;
//         size_t          time_to_die;
//         int             time_to_eat;
//         int             time_to_sleep;
//         int             nb_to_eat;
//         bool             dead_flag;
// }       t_data;



int    parsing(int ac, char *av[]);
int    process_input(char **av, int ac);
int    ft_initialize(char **av, int ac, t_data *data);
int    init_data(t_data *data);
void	init_fork(t_data *data);
int    simulation(t_data *data);
int     join_threads(t_data *data);
int     creat_threads(t_data *data);

void    *philo_routine(void *arg);
void    philo_think(t_philo *philo);
void    philo_sleep(t_philo *philo);
void    philo_eat(t_philo *philo);
void    handle_one_philo(t_philo *philo);

void     *monitor_routine(void *arg);
bool    all_philos_done(t_philo *philo);
bool    should_stop_eating(t_philo *philo);
bool    detect_death(t_philo *philo);

int	print_error(char *context, bool flag);
void	free_list(t_philo **list);
void    destroy_mutex(t_data *data);
void    clean_up(t_data *data);
size_t	ft_strlen(char *s);
t_philo	*creat_node(t_data *data, int i);
int	link_node(t_philo **head, t_philo *new_node);
size_t  get_current_time(void);
int	ft_usleep(size_t wait_time);
void    print_state(t_philo *philo, char *state);
void    increment_eat_count(t_philo *philo);
void    pickup_forks(t_philo *philo);
void    putdown_forks(t_philo *philo);
bool    finish_eating(t_philo *philo);
int	ft_isdigit(int c);
int	ft_isspace(int c);
int	ft_isempty(char *str);
int	is_sign(char *str, int i);
int     ft_atoi(char *str);




char	*ft_itoa(int n);
char	*ft_strjoin(char *s1, char *s2);
void	free_string_array(char **array);
void	ft_bzero(void *s, size_t n);
void    kill_all_philos(t_philo *philo);
void    stoop_simulation(t_data *data);

#endif