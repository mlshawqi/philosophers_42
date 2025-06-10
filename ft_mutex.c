#include "philo.h"






















// size_t	get_current_time(void)
// {
//         static struct timeval start_time;  // Will retain its value between calls
//         static int initialized = 0;         // To check if the timer is initialized
    
//         if (!initialized) {
//                 gettimeofday(&start_time, NULL); // Initialize the start time on the first call
//             initialized = 1;
//         }
    
//         struct timeval current_time;
//         gettimeofday(&current_time, NULL);
    
//         // Calculate the difference in seconds and microseconds
//         long seconds = current_time.tv_sec - start_time.tv_sec;
//         long microseconds = current_time.tv_usec - start_time.tv_usec;
    
//         // Convert total elapsed time to milliseconds
//         return (seconds * 1000) + (microseconds / 1000);
// }

// int	ft_usleep(size_t milliseconds)
// {
//         size_t	start;

//         start = get_current_time();
//         while ((get_current_time() - start) < milliseconds)
//                 usleep(500);
//         return (0);
// }

// void    ft_to_mutex(t_data *data)
// {
//         int     i;
//         int     j;

//         data->mutex_array = malloc(data->number_of_philosophers * sizeof(pthread_mutex_t));
//         if(!data->mutex_array)
//         {
//                 printf("Failed to allocate memory for array of threads.\n");
//                 exit (0);
//         }
//         data->last_eat_array= malloc(data->number_of_philosophers * sizeof(size_t));
//         if(!data->last_eat_array)
//         {
//                 printf("Failed to allocate memory for array of last time eat.\n");
//                 exit (0);
//         }
//         memset(data->last_eat_array, 0, data->number_of_philosophers);
//         // memset(data->mutex_array, 0, data->number_of_philosophers);
//         i = 0;
//         while(i < data->number_of_philosophers)
//         {
//                 j = i + 1;
//                 if(j == data->number_of_philosophers)
//                         j = 0;
//                 data->philo[i].r_fork_lock = &data->mutex_array[i];
//                 data->philo[j].l_fork_lock = &data->mutex_array[i];
//                 data->philo[i].dead_lock = &data->d_lock;
//                 data->philo[i].lst_t_eat = &data->last_eat_array[i];
//                 data->philo[i].id = i + 1;
//                 data->philo[i].number_of_philosophers = data->number_of_philosophers;
//                 data->philo[i].time_to_die = data->time_to_die;
//                 data->philo[i].time_to_eat = data->time_to_eat;
//                 data->philo[i].time_to_sleep = data->time_to_sleep;
//                 data->philo[i].nb_to_eat = data->nb_to_eat;
//                 data->philo[i].dead_flag = &data->flag_die;
//                 data->philo[i].array_l_time = &data->last_eat_array;
//                 if(data->is_stoop)
//                         data->philo[i].is_stoop = true;
//                 else
//                         data->philo[i].is_stoop = false;
//                 i++;
//         }

// }

// int    to_threads(t_data *data)
// {
//         int     i;

//         i = 0;
//         while(i < data->number_of_philosophers)
//         {

//                 pthread_mutex_init(data->philo[i].r_fork_lock, NULL); 
//                 pthread_mutex_init(data->philo[i].l_fork_lock, NULL);
//                 pthread_mutex_init(data->philo[i].dead_lock, NULL);
//                 if (pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]) != 0)
//                 {
//                         printf("Error creating thread %d\n", i);
//                         return (1);
//                 }
//                 i++;
//         }
//         i = 0;
//         while (i < data->number_of_philosophers)
//         {
//                 if(pthread_join(data->philo[i].thread, NULL) != 0)
//                 {
//                         printf("Error joing thread %d\n", i);
//                         return (1);       
//                 }
//                 i++;
//         }
//         i = 0;
//         if(data->flag_die == 1)
//         {
//                 free(data->mutex_array);
//                 free(data->last_eat_array);
//                 while(i < data->number_of_philosophers)
//                 {
//                         pthread_mutex_destroy(data->philo[i].r_fork_lock);
//                         pthread_mutex_destroy(data->philo[i].l_fork_lock);
//                         pthread_mutex_destroy(data->philo[i].dead_lock);
//                         i++;
//                 }
//                 return (0);
//         }
//         return (0);
// }