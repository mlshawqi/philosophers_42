#include "philo.h"


void    *routine(void *arg)
{
        t_philo *philo = (t_philo *)arg;

        while(true)
        {
                if(check_dead(philo) == 0)
                {
                        pthread_mutex_lock(philo->right_fork);
                        printf("%zu %d has taken a r fork\n", get_current_time(), philo->id);
                        if(check_dead(philo) == 0)
                        {
                                pthread_mutex_lock(philo->left_fork);
                                if(check_dead(philo) == 0)
                                {
                                        printf("%zu %d has taken a l fork\n", get_current_time(), philo->id);
                                        printf("%zu %d is eating\n", get_current_time(), philo->id);
                                        ft_usleep(philo->p_data->time_to_eat);
                                        philo->last_eat = get_current_time();
                                }
                                pthread_mutex_unlock(philo->left_fork);
                        }
                        pthread_mutex_unlock(philo->right_fork);
                }
                if(check_dead(philo) == 0)
                {
                        printf("%zu %d is sleeping\n", get_current_time(), philo->id);
                        ft_usleep(philo->p_data->time_to_sleep);
                }
                if(check_dead(philo) == 0)
                        printf("%zu %d is thinking\n", get_current_time(), philo->id);
                if(philo->p_data->dead_flag)
                        break;
        }
        return (NULL);
}






















// size_t    manage_l_time(size_t **array, int len)
// {
//         size_t     min;
//         int     i;

//         i = 0;
//         min = (*array)[i];
//         while(i < len)
//         {
//                 if((*array)[i] < min)
//                         min = (*array)[i];
//                 i++;
//         }
//         return (min);
// }

// void    manage_exit(size_t *array, int len)
// {
//         size_t     min;
//         int     i;
//         int     pos;

//         i = 0;
//         pos = 0;
//         min = array[i];
//         while(i < len)
//         {
//                 if(array[i] < min)
//                 {
//                         min = array[i];
//                         pos = i + 1;
//                 }
//                 i++;
//         }
//         printf("%zu %d died\n", get_current_time(), pos);
// }

// int     check_dead(t_philo *philo)
// {
//         if((get_current_time() - manage_l_time(philo->array_l_time, philo->number_of_philosophers)) >= philo->time_to_die)
//         {
//                 *philo->dead_flag = 1;
//                 // printf("        %d\n", *philo->dead_flag);
//                 // printf("%ld %d =================died\n", get_current_time(), philo->id);
//                 return (1);
//         }
//         return (0);
// }

// void    *routine(void *arg)
// {
//         t_philo *philo = (t_philo *)arg;
//         while(*philo->dead_flag == 0)
//         {
//                 if(check_dead(philo) == 0)
//                 {
//                         pthread_mutex_lock(philo->r_fork_lock);
//                         printf("%zu %d has taken a r fork\n", get_current_time(), philo->id);
//                         if(check_dead(philo) == 0)
//                         {
//                                 pthread_mutex_lock(philo->l_fork_lock);
//                                 if(check_dead(philo) == 0)
//                                 {
//                                         printf("%zu %d has taken a l fork\n", get_current_time(), philo->id);
//                                         printf("%zu %d is eating\n", get_current_time(), philo->id);
//                                         ft_usleep(philo->time_to_eat);
//                                         *philo->lst_t_eat = get_current_time();
//                                 }
//                                 pthread_mutex_unlock(philo->l_fork_lock);
//                         }
//                         pthread_mutex_unlock(philo->r_fork_lock);
//                 }
//                 if(check_dead(philo) == 0)
//                 {
//                         printf("%zu %d is sleeping\n", get_current_time(), philo->id);
//                         ft_usleep(philo->time_to_sleep);
//                 }
//                 if(check_dead(philo) == 0)
//                         printf("%zu %d is thinking\n", get_current_time(), philo->id);
//         }
//         // if(*philo->dead_flag == 1)
//         // {
//         //         // pthread_mutex_unlock((*philo).dead_lock);
//         //         // printf("%ld %d =================died\n", get_current_time(), philo->id);
//         //         // pthread_mutex_unlock((*philo).dead_lock);
//         //         return (NULL);
//         // }
//         return (NULL);
// }
