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

int main() {
    struct timeval start, current;

    // Get the current time at the start
    gettimeofday(&start, NULL);

    printf("Press Ctrl+C to stop the program.\n");

    while (1) {
        // Get the current time
        gettimeofday(&current, NULL);
        
        // Calculate the elapsed time in milliseconds
        long seconds = current.tv_sec - start.tv_sec;
        long microseconds = current.tv_usec - start.tv_usec;
        long total_milliseconds = seconds * 1000 + (microseconds / 1000);

        // Print the elapsed time
        printf("Elapsed time: %ld milliseconds\r", total_milliseconds);
        fflush(stdout); // Ensure output is printed immediately

        // Sleep for a short while to avoid busy waiting
        usleep(100000); // Sleep for 100 milliseconds
    }

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