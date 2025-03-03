#include "philo.h"


long	get_current_time(void)
{
        struct timeval start, current;
        gettimeofday(&start, NULL);
        gettimeofday(&current, NULL);
        long seconds = current.tv_sec - start.tv_sec;
        long microseconds = current.tv_usec - start.tv_usec;
        long total_milliseconds = seconds * 1000 + (microseconds / 1000);
        return (total_milliseconds);

}

void    to_eat(t_philo *philo)
{
        if(philo[philo->id].lst_t_eat + get_current_time() == philo->time_to_die)
        {
                printf("%ld %d died", get_current_time(), philo->id);
                free(philo);
                exit(0);
        }
        else if(philo->id == philo->number_of_philosophers - 1 
                && (philo[philo->id].fork == 0 && philo[0].fork == 0))
        {
                pthread_mutex_lock(&philo->fork_lock);
                philo[philo->id].fork = 1;
                philo[0].fork = 1;
                printf("%ld %d has taken a fork\n", get_current_time(), philo->id);
                printf("%ld %d has taken a fork\n", get_current_time(), philo->id);
                printf("%ld %d is eating\n", get_current_time(), philo->id);
                usleep(philo->time_to_eat);
                philo[philo->id].fork = 0;
                philo[0].fork = 0;
                philo[philo->id].lst_t_eat = get_current_time();
                pthread_mutex_unlock(&philo->fork_lock);               
        }
        else if(philo[philo->id].fork == 0 && philo[philo->id + 1].fork == 0)
        {
                pthread_mutex_lock(&philo->fork_lock);
                philo[philo->id].fork = 1;
                philo[philo->id + 1].fork = 1;
                printf("%ld %d has taken a fork\n", get_current_time(), philo->id);
                printf("%ld %d has taken a fork\n", get_current_time(), philo->id);
                printf("%ld %d is eating\n", get_current_time(), philo->id);
                usleep(philo->time_to_eat);
                philo[philo->id].fork = 0;
                philo[0].fork = 0;
                philo[philo->id].lst_t_eat = get_current_time();
                pthread_mutex_unlock(&philo->fork_lock);
        }
        // else
        //         to_eat(data, nbr);
}


void    *routine(void *arg)
{
        t_philo *philo = (t_philo *)arg;
        
        // printf("%d \n", data->id);
        // while(1)
        // {
                
                to_eat(philo);
                printf("%ld %d is sleeping\n", get_current_time(), philo->id);
                usleep(philo->time_to_sleep);
                printf("%ld %d is thinking\n", get_current_time(), philo->id);
        // }
        return (NULL);
}

int    to_threads(t_data *data)
{
        int     i;

        i = 0;
        while(i < data->number_of_philosophers)
        {
                data->philo[i].id = i + 1;
                data->philo[i].fork = 0;
                data->philo[i].lst_t_eat = 0;
                data->philo[i].number_of_philosophers = data->number_of_philosophers;
                data->philo[i].time_to_die = data->time_to_die;
                data->philo[i].time_to_eat = data->time_to_eat;
                data->philo[i].time_to_sleep = data->time_to_sleep;
                pthread_mutex_init(&data->philo[i].fork_lock, NULL); 
                if (pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]) != 0)
                {
                        printf("Error creating thread %d\n", i);
                        return (1);
                }
                i++;
        }
        i = 0;
        while (i < data->number_of_philosophers)
        {
                if(pthread_join(data->philo[i].thread, NULL) != 0)
                {
                        printf("Error joing thread %d\n", i);
                        return (1);       
                }
                i++;
        }
        return (0);
}

int     main(int argc, char *argv[])
{
        t_data  data;

        parsing(argc, argv, &data);
        data.philo = malloc(data.number_of_philosophers * sizeof(t_philo));
        if(!data.philo)
        {
                printf("Failed to allocate memory for threads.\n");
                return (1);
        }
        
        if(to_threads(&data) == 1)
        {
                free(data.philo);
                exit(1);
        }
        // pthread_mutex_destroy(&data.fork_lock);
        free(data.philo);
        // printf("number_of_philosophers %d\n", data.number_of_philosophers);
        // printf("time_to_die %d\n", data.time_to_die);
        // printf("time_to_eat %d\n", data.time_to_eat);
        // printf("time_to_sleep %d\n", data.time_to_sleep);
        // printf("nb_to_eat %d\n", data.nb_to_eat);
        // printf("------------------\n");
        return (0);
}
