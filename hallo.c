#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
int mails = 0;
pthread_mutex_t mutex;

void* routine()
{  
    int i = 0;
    while (i < 100000000)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex); //avoid race conditions
        i++;
    } 
    // printf("test from threads\n");
    // sleep(3); //check if the threads are parallel
    // printf("ending threads\n"); //check if the threads are parallel
    return(0);
}


int main(int argc, char **argv)
{
    argc = 0;
    argv = NULL;
    pthread_t t1;
    pthread_t t2;
    pthread_mutex_init(&mutex, NULL); //initialiseert mutex
    int error;

    error = pthread_create(&t1, NULL, &routine, NULL);
    error = pthread_create(&t2, NULL, &routine, NULL);
    pthread_join(t1, NULL); //wait function
    pthread_join(t2, NULL); //wait function
    printf("Number of mails: %d\n", mails);
    return(0);
}
