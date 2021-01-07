#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t thread;

pthread_mutex_t mutex;
pthread_cond_t cv;
pthread_condattr_t cattr;

void *cond_signal_fun(void *arg)
{
    /* wait for main thread wait */
    sleep(1);

    printf("lock mutex - thread\n");
    pthread_mutex_lock(&mutex);
    /* do something here */
    printf("signal - thread\n");
    pthread_cond_signal(&cv);
    printf("unlock mutex - thread\n");
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    int ret = 0;
    /* initialize a condition variable to its default value */
    ret = pthread_cond_init(&cv, &cattr);

    /* create one thread to signal the main thread */
    ret = pthread_create(&thread, NULL, cond_signal_fun, NULL);

    /* wait for signal */
    printf("lock mutex - main\n");
    pthread_mutex_lock(&mutex);
    printf("unlock mutex and wait - main\n");
    pthread_cond_wait(&cv, &mutex);
    printf("signalled and lock mutex - main\n");
    /* signalled and do something */
    pthread_mutex_unlock(&mutex);
    printf("unlock mutex - main\n");

    return ret;
}
