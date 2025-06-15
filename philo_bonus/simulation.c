#include "philo.h"

int    init_data_sem(t_data *data)
{
	data->dead_lock = sem_open(DEAD_NAME, O_CREAT | O_EXCL, 0644, 1);
        if(data->dead_lock == SEM_FAIL)
                return (print_error("sem_open dead_lock failed", false));
        data->print_lock = sem_open(PRINT_NAME, O_CREAT | O_EXCL, 0644, 1);
        if(data->print_lock == SEM_FAIL)
                return (print_error("sem_open print_lock failed", false));
        return (0);
}

int    init_philo_sem(t_philo *philo)
{
	philo->meal_lock = sem_open(philo->p_data->meals[philo->id - 1], O_CREAT | O_EXCL, 0644, 1);
        if(philo->meal_lock == SEM_FAIL)
                return (print_error("sem_open meal_lock failed", false));
        philo->eat_count_lock = sem_open(philo->p_data->eats[philo->id - 1], O_CREAT | O_EXCL, 0644, 1);
        if(philo->eat_count_lock == SEM_FAIL)
                return (print_error("sem_open eat_lock failed", false));
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
                if(init_philo_sem(tmp) != 0)
                        return (1);
                tmp->pid = fork();
                if(tmp->pid < 0)
                        return (print_error("error fork philo child", false));
                if(tmp->pid == 0)
                {
                        philo_routine(tmp);
                        clean_up(data);
                        printf("before exit\n");
                        exit(0);
                }
                tmp = tmp->next;
        }
        data->pid = fork();
        if(data->pid < 0)
                return (print_error("error fork monitor child", false));
        if(data->pid == 0)
        {
                monitor_routine(data);
                clean_up(data);
                printf("before exit in monitor\n");
                exit(0);
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
                tmp = tmp->next;
        }
        waitpid(data->pid, &status, 0);
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
