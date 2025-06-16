#include "philo.h"

void    print_state(t_philo *philo, char *state)
{
        if(detect_death(philo))
                        return ;
        sem_wait(philo->p_data->print_lock);
        if(!detect_death(philo))
                printf("%zu %d %s\n", get_current_time(), philo->id, state);
        sem_post(philo->p_data->print_lock);   
}

void    increment_eat_count(t_philo *philo)
{
        sem_wait(philo->eat_count_lock);
        philo->eat_count += 1;
        sem_post(philo->eat_count_lock);
}

void    pickup_forks(t_philo *philo)
{
        if(philo->id % 2 != 0)
        {
                sem_wait(philo->p_data->forks);
                print_state(philo , "has taken a r fork");
                sem_wait(philo->p_data->forks);
                print_state(philo ,"has taken a l fork");
        }
        else
        {
                ft_usleep(philo->p_data->time_to_eat);
                sem_wait(philo->p_data->forks);
                print_state(philo ,"has taken a l fork");
                sem_wait(philo->p_data->forks);
                print_state(philo , "has taken a r fork");
        }
}

void    putdown_forks(t_philo *philo)
{
        sem_post(philo->p_data->forks);
        sem_post(philo->p_data->forks);
}

bool    finish_eating(t_philo *philo)
{
        bool    ret;

        ret = false;
        if(philo->p_data->nb_to_eat <= 0)
                return (false);
        sem_wait(philo->eat_count_lock);
        if (philo->eat_count >= philo->p_data->nb_to_eat)
                ret = true;
        sem_post(philo->eat_count_lock);  
        return (ret);
}
