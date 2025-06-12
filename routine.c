#include "philo.h"

bool    detect_death(t_philo *philo)
{
        bool    ret;

        ret = false;
        pthread_mutex_lock(&philo->p_data->dead_lock);
        if(philo->p_data->dead_flag)
                ret = true;
        pthread_mutex_unlock(&philo->p_data->dead_lock);
        return (ret);
}

void    print_state(t_philo *philo, char *state)
{
        if(detect_death(philo))
                        return ;
        pthread_mutex_lock(&philo->p_data->print_mutex);
        if(!detect_death(philo))
                printf("%zu %d %s\n", get_current_time(), philo->id, state);
        pthread_mutex_unlock(&philo->p_data->print_mutex);   
}


void     *monitor_routine(void *arg)
{
        t_data *data = (t_data *)arg;
        t_philo *tmp;

        while(!detect_death(data->philo))
        {
                tmp = data->philo;
                while(tmp)
                {
                        pthread_mutex_lock(&tmp->meal_lock);
                        if((get_current_time() - tmp->last_meal) >= data->time_to_die)
                        {
                                pthread_mutex_lock(&data->dead_lock);
                                pthread_mutex_lock(&data->print_mutex);
                                printf("%zu %d died\n", get_current_time(), tmp->id);
                                pthread_mutex_unlock(&data->print_mutex);
                                data->dead_flag = true;
                                pthread_mutex_unlock(&data->dead_lock);
                                pthread_mutex_unlock(&tmp->meal_lock);
                                break ;
                        }
                        pthread_mutex_unlock(&tmp->meal_lock);
                        tmp = tmp->next;
                }
                usleep(500);
        }
        return (NULL);
}

void    pickup_forks(t_philo *philo)
{
        if(philo->id % 2 > 0)
        {
                pthread_mutex_lock(philo->right_fork);
                print_state(philo , "has taken a r fork");
                pthread_mutex_lock(philo->left_fork);
                print_state(philo ,"has taken a l fork");
        }
        else
        {
                pthread_mutex_lock(philo->left_fork);
                print_state(philo ,"has taken a l fork");
                pthread_mutex_lock(philo->right_fork);
                print_state(philo , "has taken a r fork");
        }
}

void    putdown_forks(t_philo *philo)
{
        if(philo->id % 2 != 0)
        {
                pthread_mutex_unlock(philo->left_fork);
                pthread_mutex_unlock(philo->right_fork);
        }
        else
        {
                pthread_mutex_unlock(philo->right_fork);
                pthread_mutex_unlock(philo->left_fork);
        }
}

void    philo_eat(t_philo *philo)
{
        if(detect_death(philo))
                        return ;
        pickup_forks(philo);
        pthread_mutex_lock(&philo->meal_lock);
        philo->last_meal = get_current_time();
        pthread_mutex_unlock(&philo->meal_lock);
        print_state(philo, "is eating");
        philo->nb_eat += 1;
        ft_usleep(philo->p_data->time_to_eat);
        putdown_forks(philo);      
}

void    philo_sleep(t_philo *philo)
{
        if(detect_death(philo))
                        return ;
        print_state(philo, "is sleeping");
        ft_usleep(philo->p_data->time_to_sleep);
}

void    philo_think(t_philo *philo)
{
        if(detect_death(philo))
                        return ;
        print_state(philo, "is thinking");
}

void    handle_one_philo(t_philo *philo)
{
        print_state(philo, "has taken a fork");
}

void    *routine(void *arg)
{
        t_philo *philo = (t_philo *)arg;

        philo->last_meal = get_current_time();
        if(philo->p_data->number_of_philosophers == 1)
                handle_one_philo(philo);
        else
        {
                while(true)
                {
                        if(detect_death(philo))
                                break;
                        philo_eat(philo);
                        philo_sleep(philo);
                        philo_think(philo);
                }
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
