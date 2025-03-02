#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void    to_eat(t_data *data)
{
        if(data->philo[data->philo->id].lst_t_eat + get_current_time() == data->time_to_die)
        {
                printf("%ld %d died", get_current_time(), data->philo->id);
                free(data->philo);
                exit(0);
        }
        else if(data->philo->id == data->number_of_philosophers - 1 
                && (data->philo[data->philo->id].fork == 0 && data->philo[0].fork == 0))
        {
                pthread_mutex_lock(&data->fork_lock);
                data->philo[data->philo->id].fork = 1;
                data->philo[0].fork = 1;
                printf("%ld %d has taken a fork\n", get_current_time(), data->philo->id);
                printf("%ld %d has taken a fork\n", get_current_time(), data->philo->id);
                printf("%ld %d is eating\n", get_current_time(), data->philo->id);
                usleep(data->time_to_eat);
                data->philo[data->philo->id].fork = 0;
                data->philo[0].fork = 0;
                data->philo[data->philo->id].lst_t_eat = get_current_time();
                pthread_mutex_unlock(&data->fork_lock);               
        }
        else if(data->philo[data->philo->id].fork == 0 && data->philo[data->philo->id + 1].fork == 0)
        {
                pthread_mutex_lock(&data->fork_lock);
                data->philo[data->philo->id].fork = 1;
                data->philo[data->philo->id + 1].fork = 1;
                printf("%ld %d has taken a fork\n", get_current_time(), data->philo->id);
                printf("%ld %d has taken a fork\n", get_current_time(), data->philo->id);
                printf("%ld %d is eating\n", get_current_time(), data->philo->id);
                usleep(data->time_to_eat);
                data->philo[data->philo->id].fork = 0;
                data->philo[0].fork = 0;
                data->philo[data->philo->id].lst_t_eat = get_current_time();
                pthread_mutex_unlock(&data->fork_lock);
        }
        // else
        //         to_eat(data, nbr);
}


void    *routine(void *arg)
{
        t_data *data = (t_data *)arg;
        
        printf("%d \n", data->philo[3].id);
        // to_eat(data);
        // printf("%ld %d is sleeping\n", get_current_time(), data->philo->id);
        // usleep(data->time_to_sleep);
        // printf("%ld %d is thinking\n", get_current_time(), data->philo->id);
        return (NULL);
}

int    to_threads(t_data *data)
{
        int     i;

        i = 0;
        while(i < data->number_of_philosophers)
        {
                data->philo[i].id = i;
                data->philo[i].fork = 0;
                data->philo[i].lst_t_eat = 0;
                if (pthread_create(&data->philo[i].thread, NULL, &routine, data) != 0)
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
        pthread_mutex_init(&data.fork_lock, NULL);
        if(to_threads(&data) == 1)
        {
                free(data.philo);
                exit(1);
        }
        pthread_mutex_destroy(&data.fork_lock);
        free(data.philo);
        // printf("number_of_philosophers %d\n", data.number_of_philosophers);
        // printf("time_to_die %d\n", data.time_to_die);
        // printf("time_to_eat %d\n", data.time_to_eat);
        // printf("time_to_sleep %d\n", data.time_to_sleep);
        // printf("nb_to_eat %d\n", data.nb_to_eat);
        // printf("------------------\n");
        return (0);
}
