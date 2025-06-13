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

void    increment_eat_count(t_philo *philo)
{
        pthread_mutex_lock(&philo->eat_count_lock);
        philo->eat_count += 1;
        pthread_mutex_unlock(&philo->eat_count_lock);
}

bool    should_stop_eating(t_philo *philo)
{
        bool    ret;

        ret = false;
        if(philo->p_data->nb_to_eat <= 0)
                return (false);
        pthread_mutex_lock(&philo->eat_count_lock);
        if (philo->eat_count >= philo->p_data->nb_to_eat)
                ret = true;
        pthread_mutex_unlock(&philo->eat_count_lock);  
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

void     *monitor_routine(void *arg)
{
        t_data *data = (t_data *)arg;
        t_philo *tmp;
        size_t  meals;

        while(!detect_death(data->philo))
        {
                tmp = data->philo;
                while(tmp)
                {
                        pthread_mutex_lock(&tmp->meal_lock);
                        meals = tmp->last_meal;
                        pthread_mutex_unlock(&tmp->meal_lock);
                        if((get_current_time() - meals) >= data->time_to_die)
                        {
                                pthread_mutex_lock(&data->dead_lock);
                                pthread_mutex_lock(&data->print_mutex);
                                printf("%zu %d died\n", get_current_time(), tmp->id);
                                pthread_mutex_unlock(&data->print_mutex);
                                data->dead_flag = true;
                                pthread_mutex_unlock(&data->dead_lock);
                                return (NULL);
                        }
                        else if(all_philos_done(data->philo))
                        {
                                pthread_mutex_lock(&data->dead_lock);
                                data->dead_flag = true;
                                pthread_mutex_unlock(&data->dead_lock);
                                return (NULL);
                        }
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
        increment_eat_count(philo);   
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

bool    finish_eating(t_philo *philo)
{
        bool    ret;

        ret = false;
        if(philo->p_data->nb_to_eat <= 0)
                return (false);
        pthread_mutex_lock(&philo->eat_count_lock);
        if (philo->eat_count >= philo->p_data->nb_to_eat)
                ret = true;
        pthread_mutex_unlock(&philo->eat_count_lock);  
        return (ret);
}

void    *philo_routine(void *arg)
{
        t_philo *philo = (t_philo *)arg;

        philo->last_meal = get_current_time();
        if(philo->p_data->number_of_philosophers == 1)
                handle_one_philo(philo);
        else
        {
                while(true)
                {
                        if(detect_death(philo) || finish_eating(philo))
                                break;
                        philo_eat(philo);
                        philo_sleep(philo);
                        philo_think(philo);
                }
        }
        return (NULL);
}

