#include "philo.h"


// long	get_current_time(void)
// {
//         struct timeval start, current;
//         gettimeofday(&start, NULL);
//         gettimeofday(&current, NULL);
//         long seconds = current.tv_sec - start.tv_sec;
//         long microseconds = current.tv_usec - start.tv_usec;
//         long total_milliseconds = seconds * 1000 + (microseconds / 1000);
//         return (total_milliseconds);

// }

// void    lock_fork(t_philo *philo)
// {
//         if(philo->fork == 0)
//         {
//                 pthread_mutex_lock(&philo->fork_lock);
//         }
// }


// void    to_eat(t_philo *philo, long time)
// {
//         if(philo[philo->id - 1].lst_t_eat + time == philo->time_to_die)
//         {
//                 printf("%ld %d died", time, philo->id);
//                 free(philo);
//                 exit(0);
//         }
//         else if(philo->id == philo->number_of_philosophers 
//                 && (philo[philo->id - 1].fork == 0 && philo[0].fork == 0))
//         {
//                 pthread_mutex_lock(&philo->fork_lock);
//                 philo[philo->id - 1].fork = 1;
//                 philo[0].fork = 1;
//                 printf("%ld %d has taken a fork\n", time, philo->id);
//                 printf("%ld %d has taken a fork\n", time, philo->id);
//                 printf("%ld %d is eating\n", time, philo->id);
//                 usleep(philo->time_to_eat);
//                 philo[philo->id - 1].fork = 0;
//                 philo[0].fork = 0;
//                 philo[philo->id - 1].lst_t_eat = time;
//                 pthread_mutex_unlock(&philo->fork_lock);               
//         }
//         else if(philo[philo->id - 1].fork == 0 && philo[philo->id].fork == 0)
//         {
//                 pthread_mutex_lock(&philo->fork_lock);
//                 philo[philo->id - 1].fork = 1;
//                 philo[philo->id].fork = 1;
//                 printf("%ld %d has taken a fork\n",time, philo->id);
//                 printf("%ld %d has taken a fork\n", time, philo->id);
//                 printf("%ld %d is eating\n", time, philo->id);
//                 usleep(philo->time_to_eat);
//                 philo[philo->id - 1].fork = 0;
//                 philo[philo->id].fork = 0;
//                 philo[philo->id - 1].lst_t_eat = time;
//                 pthread_mutex_unlock(&philo->fork_lock);
//         }
//         // else
//         //         to_eat(data, nbr);
// }




int     main(int argc, char *argv[])
{
        t_data  data;

        if(parsing(argc, argv, &data) == 1)
        {
                cleanup_data(&data);
                return (1);
        }
        if(simulation(&data) == 1)
        {
                free(data.philo);
                exit(1);
        }
        // ft_to_mutex(&data);
        // // pthread_mutex_destroy(&data.fork_lock);
        // if(data.flag_die == 1)
        // {
        //         manage_exit(data.last_eat_array, data.number_of_philosophers);
        // }
        // free(data.philo);
        return (0);

}



/*
        still problems in die and fix time. fix the algo.
*/





// printf("number_of_philosophers %d\n", data.number_of_philosophers);
// printf("time_to_die %ld\n", data.time_to_die);
// printf("time_to_eat %d\n", data.time_to_eat);
// printf("time_to_sleep %d\n", data.time_to_sleep);
// printf("nb_to_eat %d\n", data.nb_to_eat);
// printf("------------------\n");