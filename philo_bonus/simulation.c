#include "philo.h"

int    init_data_sem(t_data *data)
{
        sem_unlink("/forks");
        data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->number_of_philosophers);
        if(data->forks == SEM_FAIL)
                return (print_error("sem_open forks_lock failed", false));
        sem_unlink("/dead");
	data->dead_lock = sem_open("/dead", O_CREAT | O_EXCL, 0644, 1);
        if(data->dead_lock == SEM_FAIL)
                return (print_error("sem_open dead_lock failed", false));
        sem_unlink("/print");
        data->print_lock = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
        if(data->print_lock == SEM_FAIL)
                return (print_error("sem_open print_lock failed", false));
        return (0);
}


void    kill_all_philos(t_philo *philo)
{
        t_philo *tmp;

        tmp = philo->p_data->philo;
        while(tmp)
        {
                printf("------in killing %d\n", tmp->id);
                kill(tmp->pid, SIGKILL);
                tmp = tmp->next;
        }
}

int    init_child_sem(t_philo *philo)
{
        sem_unlink(philo->p_data->meals[philo->id - 1]);
	philo->meal_lock = sem_open(philo->p_data->meals[philo->id - 1], O_CREAT | O_EXCL, 0644, 1);
        if(philo->meal_lock == SEM_FAIL)
                return (print_error("sem_open meal_lock failed", false));
        return (0);
}

int     creat_processes(t_data *data)
{
        t_philo         *tmp;

        tmp = data->philo;
        if(init_data_sem(data) != 0)
                return (1);
        while(tmp)
        {
                tmp->pid = fork();
                if(tmp->pid < 0)
                        return (print_error("error fork philo child", false));
                if(tmp->pid == 0)
                {
                        init_child_sem(tmp);
                        philo_routine(tmp);
                        clean_up(data);
                        printf("before exit\n");
                        exit(0);
                }
                tmp = tmp->next;
        }
        return (0);
}

int     wait_processes(t_data *data)
{
        t_philo         *tmp;
        int             status;

        tmp = data->philo;
        while(tmp)
        {
                waitpid(tmp->pid, &status, 0);
                printf("exit == %d\n", WEXITSTATUS(status));
                if(WEXITSTATUS(status) == 1)
                        kill_all_philos(tmp);
                tmp = tmp->next;
        }
        return (0); 
}

int    simulation(t_data *data)
{
        if(creat_processes(data) == 1)
                return (1);
        if(wait_processes(data) == 1)
                return (1);
        return (0);
}











// int    init_data_sem(t_data *data)
// {
//         data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->number_of_philosophers);
//         if(data->forks == SEM_FAIL)
//                 return (print_error("sem_open forks_lock failed", false));
// 	data->dead_lock = sem_open("/dead", O_CREAT | O_EXCL, 0644, 1);
//         if(data->dead_lock == SEM_FAIL)
//                 return (print_error("sem_open dead_lock failed", false));
//         data->print_lock = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
//         if(data->print_lock == SEM_FAIL)
//                 return (print_error("sem_open print_lock failed", false));
//         // data->eat_counter = sem_open(EATEN_COUNTER, O_CREAT | O_EXCL, 0644, 0);
//         // if(data->eat_counter == SEM_FAIL)
//         //         return (print_error("sem_open eat_counter_lock failed", false));
//         return (0);
// }

// int    init_philo_sem(t_philo *philo)
// {
// 	philo->meal_lock = sem_open(philo->p_data->meals[philo->id - 1], O_CREAT | O_EXCL, 0644, 1);
//         if(philo->meal_lock == SEM_FAIL)
//                 return (print_error("sem_open meal_lock failed", false));
//         // philo->eat_count_lock = sem_open(philo->p_data->eats[philo->id - 1], O_CREAT | O_EXCL, 0644, 1);
//         // if(philo->eat_count_lock == SEM_FAIL)
//         //         return (print_error("sem_open eat_lock failed", false));
        
//         // philo->counter = sem_open(EATEN_COUNTER, 0);
//         // if(philo->counter == SEM_FAIL)
//         //         return (print_error("sem_open counter_lock failed", false));
//         return (0);
// }

// void    kill_all_philos(t_philo *philo)
// {
//         while(philo)
//         {
//                 kill(philo->pid, SIGKILL);
//                 philo = philo->next;
//         }
// }

// // void    stoop_simulation(t_data *data)
// // {
// //         int     i;

// //         i = 0;
// //         while(i < data->number_of_philosophers)
// //         {
// //                 sem_wait(data->eat_counter);
// //                 i++;
// //         }
// //         kill_all_philos(data->philo);
// // }

// int    init_child_sem(t_philo *philo)
// {
// 	philo->meal_lock = sem_open(philo->p_data->meals[philo->id - 1], O_CREAT | O_EXCL, 0644, 1);
//         if(philo->meal_lock == SEM_FAIL)
//                 return (print_error("sem_open meal_lock failed", false));
//         // philo->eat_count_lock = sem_open(philo->p_data->eats[philo->id - 1], 0);
//         // if(philo->eat_count_lock == SEM_FAIL)
//         //         return (print_error("sem_open eat_lock failed", false));
//         // philo->print = sem_open(PRINT_NAME, 0);
//         // if(philo->print == SEM_FAIL)
//         //         return (print_error("sem_open print_lock failed", false));
//         // philo->counter = sem_open(EATEN_COUNTER, 0);
//         // if(philo->counter == SEM_FAIL)
//         //         return (print_error("sem_open counter_lock failed", false));
//         // philo->fork = sem_open(FORKS_NAME, 0);
//         // if(philo->fork == SEM_FAIL)
//         //         return (print_error("sem_open fork_lock failed", false));
//         return (0);
// }

// int     creat_processes(t_data *data)
// {
//         t_philo         *tmp;

//         tmp = data->philo;
//         if(init_data_sem(data) != 0)
//                 return (1);
//         while(tmp)
//         {
//                 tmp->pid = fork();
//                 if(tmp->pid < 0)
//                         return (print_error("error fork philo child", false));
//                 if(tmp->pid == 0)
//                 {
//                         init_child_sem(tmp);
//                         philo_routine(tmp);
//                         clean_up(data);
//                         printf("before exit\n");
//                         exit(0);
//                 }
//                 tmp = tmp->next;
//         }
//         return (0);
// }

// int     wait_processes(t_data *data)
// {
//         t_philo         *tmp;
//         int             status;

//         tmp = data->philo;
//         while(tmp)
//         {
//                 waitpid(tmp->pid, &status, 0);
//                 tmp = tmp->next;
//         }
//         return (0); 
// }

// int    simulation(t_data *data)
// {
//         if(creat_processes(data) == 1)
//                 return (1);
//         if(wait_processes(data) == 1)
//                 return (1);
//         return (0);
// }