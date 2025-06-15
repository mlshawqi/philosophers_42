#include "philo.h"

size_t  get_current_time(void)
{
        static struct timeval   start_time;
        static int              start;
        struct timeval          current_time;
        long                    seconds;
        long                    microseconds;

        if(!start)
        {
                if (gettimeofday(&start_time, NULL) == -1)
		        return (print_error("gettimeofday() error\n", NULL));
                start = 1;
        }
        if (gettimeofday(&current_time, NULL) == -1)
		        return (print_error("gettimeofday() error\n", NULL));
        seconds = current_time.tv_sec - start_time.tv_sec;
        microseconds = current_time.tv_usec - start_time.tv_usec;
        return ((seconds * 1000) + (microseconds / 1000));
}


int	ft_usleep(size_t wait_time)
{
        size_t	start_time;

        start_time = get_current_time();
        while ((get_current_time() - start_time) < wait_time)
                usleep(500);
        return (0);
}