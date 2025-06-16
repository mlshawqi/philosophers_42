#include "philo.h"

// void	init_fork(t_data *data)
// {
// 	int	i;
// 	t_philo		*tmp;

// 	i = 0;
// 	tmp = data->philo;
// 	while(i < data->number_of_philosophers)
// 	{
// 		if(!tmp->prev)
// 			tmp->left_fork = data->sem_array[data->number_of_philosophers - 1];
// 		tmp->right_fork = data->sem_array[i];
// 		if(tmp->next)
// 			tmp->next->left_fork = data->sem_array[i];
// 		i++;
// 		tmp = tmp->next;
// 	}
// }
// int    get_name(t_data *data)
// {
//         int     i;
//         char    *tmp;

//         data->names = malloc(sizeof(char *) * (data->number_of_philosophers + 1));
//         if(!data->names)
//                 return (print_error("data_names", true));
//         i = 0;
//         ft_bzero(data->names, (data->number_of_philosophers + 1) * sizeof(char *));
//         while(i < data->number_of_philosophers)
//         {
//                 tmp = NULL;
//                 tmp = ft_itoa(i);
//                 if(!tmp)
//                 {
//                         free_string_array(data->names);
//                         return (print_error("data_names", true));
//                 }
//                 data->names[i] = ft_strjoin("/name", tmp);
//                 free(tmp);
//                 if(!data->names[i])
//                 {
//                         free_string_array(data->names);
//                         return (print_error("data_names", true));
//                 }
//                 i++;
//         }
//         return (0);
// }

char    *gave_name(char *str, int i)
{
        char    *tmp;
        char    *tmp2;
        char    *name;

        tmp = NULL;
        tmp2 = NULL;
        name = NULL;
        tmp = ft_itoa(i);
        if(!tmp)
                return (NULL);
        tmp2 = ft_strjoin("/", str);
        if(!tmp2)
        {
                free(tmp);
                return (NULL);                
        }
        name = ft_strjoin(tmp2, tmp);
        free(tmp);
        free(tmp2);
        if(!name)
                return (NULL);
        return (name);
}

char    **get_names(t_data *data, char *name)
{
        int     i;
        char    **names;

        names = NULL;
        names = malloc(sizeof(char *) * (data->number_of_philosophers + 1));
        if(!names)
        {
                print_error("array of names", true);
                return (NULL);
        }
        i = 0;
        ft_bzero(names, (data->number_of_philosophers + 1) * sizeof(char *));
        while(i < data->number_of_philosophers)
        {
                names[i] = gave_name(name, i);
                if(!names[i])
                {
                        free_string_array(names);
                        print_error("data_names", true);
                        return (NULL);
                }
                i++;
        }
        return (names);
}

int    init_data(t_data *data)
{
        int     i;

	i = 0;
        while(i < data->number_of_philosophers)
        {
                if(link_node(&data->philo, creat_node(data, i + 1)) == 1)
                        return (1);
                i++;
        }
        data->meals = get_names(data, "meals");
        data->eats = get_names(data, "eat");
        if(!data->meals || !data->eats)
                return (1);
	// init_fork(data);
	return (0);
}

int    ft_initialize(char **av, int ac, t_data *data)
{
        data->philo = NULL;
        data->meals = NULL;
        data->eats = NULL;
        data->time_to_die = ft_atoi(av[2]);
        data->time_to_eat = ft_atoi(av[3]);
        data->time_to_sleep = ft_atoi(av[4]);
        data->dead_flag = false;
        data->nb_to_eat = 0;
        data->number_of_philosophers = ft_atoi(av[1]);
        if(data->number_of_philosophers > 200 || data->number_of_philosophers <= 0)
        {
                write(2, "Error: '", 8);
                write(2, av[1], ft_strlen(av[1]));
                print_error("' there must be between 1 and 200 philosophers.", false);
                return (1);
        }
        if(ac == 6)
        {
                data->nb_to_eat = ft_atoi(av[5]);
                if(data->nb_to_eat == 0)
                        data->dead_flag = true;
        }
        if(init_data(data) == 1)
                return (1);
        return (0);
}

        // data->sem_array = NULL;
        // data->names = NULL;
        // data->meals = NULL;
        // data->eats = NULL;
