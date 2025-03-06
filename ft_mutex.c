#include "philo.h"


size_t	get_current_time(void)
{
        static struct timeval start_time;  // Will retain its value between calls
        static int initialized = 0;         // To check if the timer is initialized
    
        if (!initialized) {
                gettimeofday(&start_time, NULL); // Initialize the start time on the first call
            initialized = 1;
        }
    
        struct timeval current_time;
        gettimeofday(&current_time, NULL);
    
        // Calculate the difference in seconds and microseconds
        long seconds = current_time.tv_sec - start_time.tv_sec;
        long microseconds = current_time.tv_usec - start_time.tv_usec;
    
        // Convert total elapsed time to milliseconds
        return (seconds * 1000) + (microseconds / 1000);
}

int	ft_usleep(size_t milliseconds)
{
        size_t	start;

        start = get_current_time();
        while ((get_current_time() - start) < milliseconds)
                usleep(500);
        return (0);
}

void    ft_to_mutex(t_data *data)
{
        int     i;
        int     j;

        data->mutex_array = malloc(data->number_of_philosophers * sizeof(pthread_mutex_t));
        if(!data->mutex_array)
        {
                printf("Failed to allocate memory for array of threads.\n");
                exit (0);
        }
        memset(data->mutex_array, 0, data->number_of_philosophers);
        i = 0;
        while(i < data->number_of_philosophers)
        {
                j = i + 1;
                if(j == data->number_of_philosophers)
                        j = 0;
                data->philo[i].r_fork_lock = &data->mutex_array[i];
                data->philo[j].l_fork_lock = &data->mutex_array[i];
                data->philo[i].dead_lock = &data->d_lock;
                i++;
        }

}