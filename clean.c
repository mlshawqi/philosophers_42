#include "philo.h"

void	clean_philo(t_philo **list)
{
	t_philo         *p;

	
	if (list == NULL || *list == NULL)
		return ;
	while (*list != NULL)
	{
		p = (*list)->next;
		free(*list);
		*list = p;
	}
	free(*list);
	*list = NULL;
}

void    cleanup_data(t_data *data)
{
        if(data->philo)
                clean_philo(&data->philo);
}