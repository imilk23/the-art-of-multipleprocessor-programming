// g++ -lpthread peterson.cpp -o peterson
 
#include <iostream>
#include <pthread.h>
using namespace std;
 
int flag[2];
int turn;
const int MAX = 1e9;
int ans = 0;
 
void lock_init()
{
    flag[0] = flag[1] = 0;
    turn = 0;
}

void lock(int self)
{
    flag[self] = 1;

    turn = 1-self;

    while (flag[1-self]==1 && turn==1-self){
        sched_yield();
    }
}

void unlock(int self)
{
    flag[self] = 0;
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