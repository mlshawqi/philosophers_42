#include "philo.h"

bool    detect_death(t_philo *philo)
{
        bool    ret;

        ret = false;
        sem_wait(philo->p_data->dead_lock);
        if(philo->p_data->dead_flag)
                ret = true;
        sem_post(philo->p_data->dead_lock);
        return (ret);
}

bool    should_stop_eating(t_philo *philo)
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

bool    all_philos_done(t_philo *philo)
{
        while(philo)
        {
                if(should_stop_eating(philo))
                        philo = philo->next;
                else
                        return (false);
        }
        return (true);
}

bool    simulation_stop(t_data *data, t_philo *tmp)
{
        size_t  meals;

        sem_wait(tmp->meal_lock);
        meals = tmp->last_meal;
        sem_post(tmp->meal_lock);
        if((get_current_time() - meals) >= data->time_to_die)
        {
                sem_wait(data->dead_lock);
                sem_post(&data->print_lock);
                printf("%zu %d died\n", get_current_time(), tmp->id);
                sem_post(data->print_lock);
                data->dead_flag = true;
                sem_post(data->dead_lock);
                return (true);
        }
        else if(all_philos_done(data->philo))
        {
                sem_wait(data->dead_lock);
                data->dead_flag = true;
                sem_post(data->dead_lock);
                return (true);
        }
        return (false);
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
                        if(simulation_stop(data, tmp))
                                return (NULL);
                        tmp = tmp->next;
                }
                usleep(500);
        }
        return (NULL);
}
