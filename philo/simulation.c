#include "philo.h"

int     creat_threads(t_data *data)
{
        t_philo         *tmp;

        tmp = data->philo;
        pthread_mutex_init(&data->dead_lock, NULL); 
        pthread_mutex_init(&data->print_mutex, NULL);
        pthread_mutex_init(&data->time_lock, NULL);
        while(tmp)
        {
                pthread_mutex_init(&tmp->meal_lock, NULL);
                pthread_mutex_init(&tmp->eat_count_lock, NULL);
                if (pthread_create(&tmp->thread, NULL, &philo_routine, tmp) != 0)
                {
                        printf("Error creating thread %d\n", tmp->id);
                        return (1);
                }
                tmp = tmp->next;
        }
        if (pthread_create(&data->monitor, NULL, &monitor_routine, data) != 0)
        {
                printf("Error creating monitor thread\n");
                return (1);
        }
        return (0);
}

int     join_threads(t_data *data)
{
        t_philo         *tmp;

        tmp = data->philo;
        while(tmp)
        {
                if (pthread_join(tmp->thread, NULL) != 0)
                {
                        printf("Error joing thread %d\n", tmp->id);
                        return (1);
                }
                tmp = tmp->next;
        }
        if (pthread_join(data->monitor, NULL) != 0)
        {
                printf("Error joing monitor thread\n");
                return (1);
        }
        return (0); 
}

int    simulation(t_data *data)
{
        if(creat_threads(data) == 1)
                return (1);
        if(join_threads(data) == 1)
                return (1);
        return (0);
}
