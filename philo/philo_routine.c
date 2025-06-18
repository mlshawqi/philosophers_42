#include "philo.h"

void    handle_one_philo(t_philo *philo)
{
        pthread_mutex_lock(philo->right_fork);
        print_state(philo , "has taken a r fork");
}

void    philo_eat(t_philo *philo)
{
        if(detect_death(philo))
                        return ;
        pickup_forks(philo);
        if(detect_death(philo))
                        return ;
        pthread_mutex_lock(&philo->meal_lock);
        philo->last_meal = get_current_time();
        philo->is_eating = true;
        pthread_mutex_unlock(&philo->meal_lock);
        print_state(philo, "is eating");
        ft_usleep(philo->p_data->time_to_eat);
        pthread_mutex_lock(&philo->meal_lock);
        philo->is_eating = false;
        pthread_mutex_unlock(&philo->meal_lock);
        putdown_forks(philo);
        increment_eat_count(philo);  
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
        print_state(philo, "is thinking");
}

void    *philo_routine(void *arg)
{
        t_philo *philo = (t_philo *)arg;
        int i = 0;

        pthread_mutex_lock(&philo->meal_lock);
        philo->last_meal = get_current_time();
        pthread_mutex_unlock(&philo->meal_lock);
        if(philo->p_data->number_of_philosophers == 1)
                handle_one_philo(philo);
        else
        {
                while(!detect_death(philo))
                {
                        philo_think(philo);
                        if(i == 0 && (philo->id % 2 == 0))
                                ft_usleep((philo->p_data->time_to_eat) / 2);
                        philo_eat(philo);
                        philo_sleep(philo);
                        i++;
                }
        }
        return (NULL);
}