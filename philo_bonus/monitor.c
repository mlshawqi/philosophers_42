#include "philo.h"

bool    detect_death(t_philo *philo)
{
        bool    ret;

        ret = false;
        sem_wait(philo->p_data->dead_lock);
        if(philo->p_data->dead_flag)
        {
                printf("flag catshed %d\n", philo->id);
                ret = true;
        }
        sem_post(philo->p_data->dead_lock);
        return (ret);
}

// bool    should_stop_eating(t_philo *philo)
// {
//         bool    ret;

//         ret = false;
//         if(philo->p_data->nb_to_eat <= 0)
//                 return (false);
//         sem_wait(philo->eat_count_lock);
//         if (philo->eat_count >= philo->p_data->nb_to_eat)
//                 sem_post(philo->counter);
//         sem_post(philo->eat_count_lock);  
//         return (ret);
// }

bool    simulation_stop(t_philo *tmp)
{
        size_t  meals;

        if(detect_death(tmp))
                return (false);
        sem_wait(tmp->meal_lock);
        meals = tmp->last_meal;
        sem_post(tmp->meal_lock);
        // should_stop_eating(tmp);
        if((get_current_time() - meals) >= tmp->p_data->time_to_die)
        {
                sem_wait(tmp->p_data->dead_lock);
                tmp->p_data->dead_flag = true;
                sem_wait(tmp->p_data->print_lock);
                printf("%zu %d died\n", get_current_time(), tmp->id);
                sem_post(tmp->p_data->print_lock);
                // ft_usleep(10);
                // sem_post(tmp->p_data->dead_lock);
                return (true);
        }
        return (false);
}

void     *monitor_routine(void *arg)
{
        t_philo *philo = (t_philo *)arg;

        while(!detect_death(philo))
        {
                if(simulation_stop(philo))
                {
                        clean_up(philo->p_data);
                        exit (1);
                }
                usleep(500);
        }
        return (NULL);
}














// bool    detect_death(t_philo *philo)
// {
//         bool    ret;

//         ret = false;
//         sem_wait(philo->p_data->dead_lock);
//         if(philo->p_data->dead_flag)
//                 ret = true;
//         sem_post(philo->p_data->dead_lock);
//         return (ret);
// }

// bool    should_stop_eating(t_philo *philo)
// {
//         bool    ret;

//         ret = false;
//         if(philo->p_data->nb_to_eat <= 0)
//                 return (false);
//         sem_wait(philo->eat_count_lock);
//         if (philo->eat_count >= philo->p_data->nb_to_eat)
//                 sem_post(philo->counter);
//         sem_post(philo->eat_count_lock);  
//         return (ret);
// }

// bool    simulation_stop(t_philo *tmp)
// {
//         size_t  meals;

//         sem_wait(tmp->meal_lock);
//         meals = tmp->last_meal;
//         sem_post(tmp->meal_lock);
//         printf("hereeeeesssssssss\n");
//         should_stop_eating(tmp);
//         if((get_current_time() - meals) >= tmp->p_data->time_to_die)
//         {
//                 printf("hereee\n");
//                 sem_wait(tmp->p_data->print_lock);
//                 printf("%zu %d died\n", get_current_time(), tmp->id);
//                 sem_post(tmp->p_data->print_lock);
//                 printf("here after\n");
//                 return (true);
//         }
//         return (false);
// }

// void    post_all(t_philo *philo)
// {
//         t_philo *tmp;

//         printf("here\n");
//         tmp = philo->p_data->philo;
//         while(tmp)
//         {
//                 sem_wait(tmp->eat_count_lock);
//                 if (tmp->eat_count < tmp->p_data->nb_to_eat)
//                         sem_post(tmp->counter);
//                 sem_post(tmp->eat_count_lock);
//                 tmp = tmp->next;
//         }
//         printf("after here\n");
// }

// void     *monitor_routine(void *arg)
// {
//         t_philo *philo = (t_philo *)arg;

//         while(true)
//         {
//                 if(simulation_stop(philo))
//                 {
//                         post_all(philo);
//                         return (NULL);
//                 }
//                 usleep(500);
//         }
//         return (NULL);
// }