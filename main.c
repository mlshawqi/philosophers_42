#include "philo.h"


void    *routine(void *arg)
{
        t_data *data = (t_data *)arg;
        struct timeval start, current;
        int i = 0;

        gettimeofday(&start, NULL);
        while (1) {
            gettimeofday(&current, NULL);
            long seconds = current.tv_sec - start.tv_sec;
            long microseconds = current.tv_usec - start.tv_usec;
            long total_milliseconds = seconds * 1000 + (microseconds / 1000);
    
            if(total_milliseconds != data->time_to_die)
            {
                printf("%ld %d is eating\n", total_milliseconds, i);
                usleep(data->time_to_eat);
                printf("%ld %d is sleeping\n", total_milliseconds, i);
                usleep(data->time_to_sleep);
                printf("%ld %d is thinking\n", total_milliseconds, i);
            }
            else
            {
                printf("you die\n");
                exit(1);
            }
        //     printf("Elapsed time: %ld milliseconds\r", total_milliseconds);
        //     fflush(stdout); // Ensure output is printed immediately
    
            // Sleep for a short while to avoid busy waiting
        //     usleep(100000); // Sleep for 100 milliseconds
            i++;
        }
        printf("never %d\n", data->nb_to_eat);
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
        if(to_threads(&data) == 1)
        {
                free(data.philo);
                exit(1);
        }
        free(data.philo);
        // printf("number_of_philosophers %d\n", data.number_of_philosophers);
        // printf("time_to_die %d\n", data.time_to_die);
        // printf("time_to_eat %d\n", data.time_to_eat);
        // printf("time_to_sleep %d\n", data.time_to_sleep);
        // printf("nb_to_eat %d\n", data.nb_to_eat);
        // printf("------------------\n");
        return (0);
}
