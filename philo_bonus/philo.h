/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machaouk <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-19 21:19:29 by machaouk          #+#    #+#             */
/*   Updated: 2025-06-19 21:19:29 by machaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t			monitor;
	sem_t				*meal_lock;
	bool				is_eating;
	int					id;
	pid_t				pid;
	size_t				last_meal;
	int					eat_count;
	struct s_philo		*next;
	struct s_philo		*prev;
	t_data				*p_data;
}						t_philo;

typedef struct s_data
{
	t_philo				*philo;
	sem_t				*forks;
	sem_t				*dead_lock;
	sem_t				*print_lock;
	sem_t				*time_lock;
	char				**meals;
	char				**eats;
	int					nbr_philos;
	size_t				time_to_die;
	int					t_eat;
	int					t_sleep;
	int					nb_to_eat;
	bool				dead_flag;
}						t_data;

int						parsing(int ac, char *av[]);
int						process_input(char **av, int ac);
int						ft_initialize(char **av, int ac, t_data *data);
int						init_data(t_data *data);
void					init_fork(t_data *data);
int						simulation(t_data *data);
int						join_threads(t_data *data);
int						creat_threads(t_data *data);

void					*philo_routine(void *arg);
void					philo_think_sleep(t_philo *philo, bool hint);
void					philo_eat(t_philo *philo);
void					handle_one_philo(t_philo *philo);

void					*monitor_routine(void *arg);
bool					all_philos_done(t_philo *philo);
bool					should_stop_eating(t_philo *philo, int eat_counter);
bool					detect_death(t_philo *philo);

int						print_error(char *context, bool flag);
void					free_list(t_philo **list, bool hint);
void					destroy_mutex(t_data *data);
void					clean_up(t_data *data, bool hint);
size_t					ft_strlen(char *s);
t_philo					*creat_node(t_data *data, int i);
int						link_node(t_philo **head, t_philo *new_node);
size_t					get_current_time(t_philo *philo);
int						ft_usleep(t_philo *philo, size_t wait_time);
void					print_state(t_philo *philo, char *state);
void					increment_eat_count(t_philo *philo);
void					pickup_forks(t_philo *philo);
void					putdown_forks(t_philo *philo);
bool					finish_eating(t_philo *philo);
int						ft_isdigit(int c);
int						ft_isspace(int c);
int						ft_isempty(char *str);
int						is_sign(char *str, int i);
int						ft_atoi(char *str);

char					*ft_itoa(int n);
char					*ft_strjoin(char *s1, char *s2);
void					free_string_array(char **array);
void					ft_bzero(void *s, size_t n);
void					kill_all_philos(t_philo *philo);
void					stoop_simulation(t_data *data);
void					apply_delay(t_philo *philo, int i, bool hint);

#endif