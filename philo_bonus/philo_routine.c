#include "philo.h"

void    handle_one_philo(t_philo *philo)
{
        print_state(philo, "has taken a fork");
}

void    philo_eat(t_philo *philo)
{
        pickup_forks(philo);
        sem_wait(philo->meal_lock);
        philo->last_meal = get_current_time();
        sem_post(philo->meal_lock);
        print_state(philo, "is eating");
        // increment_eat_count(philo);   
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


int     handle_monitor(t_philo *philo, bool create)
{
        if(create)
        {
                if (pthread_create(&philo->monitor, NULL, &monitor_routine, philo) != 0)
                {
                        printf("Error creating monitor thread\n");
                        return (1);
                }
        }
        else
        {
                if (pthread_join(philo->monitor, NULL) != 0)
                {
                        printf("Error joing monitor thread\n");
                        return (1);
                }
        }
        return (0);
}

void    *philo_routine(void *arg)
{
        t_philo *philo = (t_philo *)arg;

        philo->last_meal = get_current_time();
        if(philo->p_data->number_of_philosophers == 1)
                handle_one_philo(philo);
        else
        {
                handle_monitor(philo, true);
                while(true)
                {
                        philo_think(philo);
                        philo_eat(philo);
                        philo_sleep(philo);
                }
                handle_monitor(philo, false);
        }
        return (NULL);
}






















// void    handle_one_philo(t_philo *philo)
// {
//         print_state(philo, "has taken a fork");
// }

// void    philo_eat(t_philo *philo)
// {
//         pickup_forks(philo);
//         sem_wait(philo->meal_lock);
//         philo->last_meal = get_current_time();
//         sem_post(philo->meal_lock);
//         print_state(philo, "is eating");
//         increment_eat_count(philo);   
//         ft_usleep(philo->p_data->time_to_eat);
//         putdown_forks(philo);
// }

// void    philo_sleep(t_philo *philo)
// {
//         if(detect_death(philo))
//                         return ;
//         print_state(philo, "is sleeping");
//         ft_usleep(philo->p_data->time_to_sleep);
// }

// void    philo_think(t_philo *philo)
// {
//         if(detect_death(philo))
//                         return ;
//         print_state(philo, "is thinking");
// }


// int     handle_monitor(t_philo *philo, bool create)
// {
//         if(create)
//         {
//                 if (pthread_create(&philo->monitor, NULL, &monitor_routine, philo) != 0)
//                 {
//                         printf("Error creating monitor thread\n");
//                         return (1);
//                 }
//         }
//         else
//         {
//                 if (pthread_join(philo->monitor, NULL) != 0)
//                 {
//                         printf("Error joing monitor thread\n");
//                         return (1);
//                 }
//         }
//         return (0);
// }

// void    *philo_routine(void *arg)
// {
//         t_philo *philo = (t_philo *)arg;

//         philo->last_meal = get_current_time();
//         if(philo->p_data->number_of_philosophers == 1)
//                 handle_one_philo(philo);
//         else
//         {
//                 handle_monitor(philo, true);
//                 while(true)
//                 {
//                         philo_eat(philo);
//                         philo_sleep(philo);
//                         philo_think(philo);
//                 }
//                 handle_monitor(philo, false);
//         }
//         return (NULL);
// }