# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/wait.h>

int main()
{
        int i = 0;
        int pid = fork();

        if(pid == -1)
                return (1);
        if(pid != 0)
                i++;
        printf("i %d \n", i);
        // if(pid != 0)
        //         wait(NULL);
        return (0);
}


// void    *myturn()
// {
//         i++;
//         printf("my turn %d \n", i);
//         sleep(1);
//         return (NULL);
// }

// void    *yourturn()
// {
//         printf("your turn %d \n", i);
//         sleep(1);
//         return (NULL);
// }

// int     main()
// {
//         pthread_t       t1, t2;

//         pthread_create(&t1, NULL, &myturn, NULL);
//         pthread_create(&t2, NULL, &yourturn, NULL);
//         // i += 2;
//         // pthread_join(t1, NULL);
//         // pthread_join(t2, NULL);
//         // myturn("arg");
//         // yourturn("arg");
// }