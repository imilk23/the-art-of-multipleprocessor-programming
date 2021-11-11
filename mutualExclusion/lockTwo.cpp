#include <iostream>
#include <pthread.h>
#include<map>
using namespace std;

int victim;
const int MAX = 1e9;
int ans = 0;

void lock_init()
{
}

void lock(int self){
    victim = self;
    while(victim == self){
        // wait
    }
}

void unlock(int self){
}

void* func(void *s)
{
    int i = 0;
    int *self = (int *)s;
    cout << "Thread Entered: " << *self << endl;
 
    lock(*self);
 
    // Critical section (Only one thread
    // can enter here at a time)
    for (i=0; i<MAX; i++)
        ans++;
 
    unlock(*self);
}

int main()
{
    pthread_t p1, p2;
    lock_init();
 
    // Create two threads (both run func)
    int t0 = 0;
    int t1 = 1;
    pthread_create(&p1, NULL, func, &t0);
    pthread_create(&p2, NULL, func, &t1);
 
    // Wait for the threads to end.
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
 
    printf("Actual Count: %d | Expected Count: %d\n",
                                        ans, MAX*2);
 
    return 0;
}