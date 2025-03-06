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



void    *routine(void *arg)
{
        t_philo *philo = (t_philo *)arg;
        int i = 0;

        while(i < philo->nb_to_eat && ((get_current_time() - philo->lst_t_eat) < philo->time_to_die))
        {       
                if((get_current_time() - philo->lst_t_eat) >= philo->time_to_die)
                {
                        pthread_mutex_lock(philo->dead_lock);
                        printf("%ld %d died\n", get_current_time(), philo->id);
                        pthread_mutex_unlock(philo->dead_lock);
                        pthread_exit(NULL);
                        exit(0);   
                }
                pthread_mutex_lock(philo->r_fork_lock);
                printf("%zu %d has taken a fork\n", get_current_time(), philo->id);
                pthread_mutex_lock(philo->l_fork_lock);
                printf("%zu %d has taken a fork\n", get_current_time(), philo->id);
                printf("%zu %d --------------------is eating\n", get_current_time(), philo->id);
                ft_usleep(philo->time_to_eat);
                philo->lst_t_eat = get_current_time();
                pthread_mutex_unlock(philo->r_fork_lock);
                pthread_mutex_unlock(philo->l_fork_lock);
                ft_usleep(philo->time_to_sleep);
                printf("%zu %d is sleeping\n", get_current_time(), philo->id);
                printf("%zu %d is thinking\n", get_current_time(), philo->id);
                i++;
        }
        return (NULL);
}

int    to_threads(t_data *data)
{
        int     i;

        i = 0;
        while(i < data->number_of_philosophers)
        {
                data->philo[i].id = i + 1;
                data->philo[i].lst_t_eat = 0;
                data->philo[i].number_of_philosophers = data->number_of_philosophers;
                data->philo[i].time_to_die = data->time_to_die;
                data->philo[i].time_to_eat = data->time_to_eat;
                data->philo[i].time_to_sleep = data->time_to_sleep;
                data->philo[i].nb_to_eat = data->nb_to_eat;
                data->philo[i].dead_flag = 0;
                pthread_mutex_init(data->philo[i].r_fork_lock, NULL); 
                pthread_mutex_init(data->philo[i].l_fork_lock, NULL);
                pthread_mutex_init(data->philo[i].dead_lock, NULL);
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
        ft_to_mutex(&data);
        if(to_threads(&data) == 1)
        {
                free(data.philo);
                exit(1);
        }
        // pthread_mutex_destroy(&data.fork_lock);
        free(data.philo);
        return (0);

}









// printf("number_of_philosophers %d\n", data.number_of_philosophers);
// printf("time_to_die %ld\n", data.time_to_die);
// printf("time_to_eat %d\n", data.time_to_eat);
// printf("time_to_sleep %d\n", data.time_to_sleep);
// printf("nb_to_eat %d\n", data.nb_to_eat);
// printf("------------------\n");