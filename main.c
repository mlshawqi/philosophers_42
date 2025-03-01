#include "philo.h"

void    *routine(void *arg)
{
        t_data *data = (t_data *)arg;
        struct timeval start, current;

        gettimeofday(&start, NULL);
        while (1) {
            gettimeofday(&current, NULL);
            long seconds = current.tv_sec - start.tv_sec;
            long microseconds = current.tv_usec - start.tv_usec;
            long total_milliseconds = seconds * 1000 + (microseconds / 1000);
    
            if(total_milliseconds == 0)
            {
                printf("--is eating %ld\n", total_milliseconds);
                break;
                // printf("%d is sleeping\n", i);
                // printf("%d is thinking\n", i);                
            }
            printf("Elapsed time: %ld milliseconds\r", total_milliseconds);
            fflush(stdout); // Ensure output is printed immediately
    
            // Sleep for a short while to avoid busy waiting
            usleep(100000); // Sleep for 100 milliseconds
        }
        printf("never %d\n", data->nb_to_eat);
        return (NULL);
}

int     main(int argc, char *argv[])
{
        t_data  data;
        int     i;

        parsing(argc, argv, &data);
        data.philo = malloc(data.number_of_philosophers * sizeof(pthread_t));
        if(!data.philo)
        {
                printf("Failed to allocate memory for threads.\n");
                return (1);
        }
        i = 0;
        while(i < data.number_of_philosophers)
        {
                if (pthread_create(data.philo + i, NULL, &routine, &data) != 0)
                {
                        printf("Error creating thread %d\n", i);
                        free(data.philo);
                        return 1;
                }
                i++;
        }
        i = 0;
        while (i < data.number_of_philosophers)
        {
                if(pthread_join(data.philo[i], NULL) != 0)
                {
                        printf("Error joing thread %d\n", i);
                        free(data.philo);
                        return 1;       
                }
                i++;
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
