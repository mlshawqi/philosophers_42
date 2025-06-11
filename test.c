# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/wait.h>


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include <stdio.h>
#include <sys/time.h>
#include <unistd.h> // For usleep


unsigned long  get_current_time(void)
{
        static struct timeval   start_time;
        static int              start;
        struct timeval          current_time;
        long                    seconds;
        long                    microseconds;

        if(!start)
        {
                gettimeofday(&start_time, NULL);
                start = 1;
        }
        gettimeofday(&current_time, NULL);
        seconds = current_time.tv_sec - start_time.tv_sec;
        microseconds = current_time.tv_usec - start_time.tv_usec;
        return ((seconds * 1000) + (microseconds / 1000));
}


int main() {
    printf("time %ld\n", get_current_time());
    usleep(100000);
    printf("time %ld\n", get_current_time());
    printf("time %ld\n", get_current_time());
    return 0;
}


// void* threadFunction(void* arg) {
//     int num = *(int*)arg;
//     printf("Thread %d is running.\n", num);
//     sleep(1); 
//     printf("Thread %d is exiting.\n", num);
//     return NULL;
// }

// int main() {
//     pthread_t threads[3];
//     int threadArgs[3];
    
//     for (int i = 0; i < 3; i++) {
//         threadArgs[i] = i + 1; 
//         if (pthread_create(&threads[i], NULL, threadFunction, &threadArgs[i]) != 0) {
//             perror("Failed to create thread");
//             return 1;
//         }
//     }

//     // No pthread_join here
//     printf("Main thread is exiting.\n"); // This may print before threads complete

//     return 0;
// }

// void* threadFunction(void* arg) {
//     int num = *(int*)arg;
//     printf("Thread %d is running.\n", num);
//     // Simulate some work
// //     sleep(1); 
//     printf("Thread %d is exiting.\n", num);
//     return NULL;
// }

// int main() {
//     pthread_t threads[3];
//     int threadArgs[3];

//     for (int i = 0; i < 3; i++) {
//         threadArgs[i] = i + 1; // Assigning argument for thread
//         if (pthread_create(&threads[i], NULL, threadFunction, &threadArgs[i]) != 0) {
//             perror("Failed to create thread");
//             return 1;
//         }
//     }

//     // Wait for all threads to complete
//     for (int i = 0; i < 3; i++) {
//         pthread_join(threads[i], NULL);
//     }

//     printf("All threads have completed.\n");

//     return 0;
// }













// int main()
// {
//         int i = 0;
//         int pid = fork();

//         if(pid == -1)
//                 return (1);
//         if(pid != 0)
//                 i++;
//         printf("i %d \n", i);
//         // if(pid != 0)
//         //         wait(NULL);
//         return (0);
// }


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