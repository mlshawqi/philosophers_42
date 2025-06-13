#include "philo.h"

int     main(int argc, char *argv[])
{
        t_data  data;

        if(parsing(argc, argv) == 1)
                return (1);
        // if(ft_initialize(argv, argc, &data) == 1)
        // {
        //         clean_up(&data);
        //         return (1);
        // }
        // if(simulation(&data) == 1)
        // {
        //         clean_up(&data);
        //         return (1);
        // }
        // clean_up(&data);
        return (0);

}