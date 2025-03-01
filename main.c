#include "philo.h"

void    *routine()
{
        int i = 1;
        while(i <= 2)
        {
                printf("%d is eating\n", i);
                printf("%d is sleeping\n", i);
                printf("%d is thinking\n", i);
                i++;
        }
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
