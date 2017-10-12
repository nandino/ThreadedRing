
#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>

#include"ThreadedRing.h"

#define N 10
sem_t empty,full,mutex;

void *b[N];
int in=0, out=0,i=0;

void* thread_fun1(void* arg)
{
	sem_wait(&empty);
	sem_wait(&mutex);  
	b[(in)%(N)] =i;
	printf("Prod=B[%d] = ",in);
	printf("%d\n",i);
	in++;
	i++;

	sem_post(&mutex);
	sem_post(&full);
	sleep(1);
//	pthread_exit("producer\n");
}

void * thread_fun2(void* arg)
{
	sem_wait(&full);
	sem_wait(&mutex); 

//	sleep(1);
	void *result = b[(out)% (N)];
	printf("Cons=B[ %d] = ",out);
 	printf("%d\n",b[(out) % (N)]);
	out++;
	sem_post(&mutex);
 	sem_post(&empty);
	sleep(1);
// 	pthread_exit("consumer\n");
}



int main(){
	
	pthread_t pid1[pCANT_THREADS],pid2[cCANT_THREADS];

	sem_init(&empty,0,N);
	sem_init(&full,0,0);
	sem_init(&mutex,1,1);

	int ptid,ctid,ringpos;

	while(out<25){
		for (ptid = 0; ptid < pCANT_THREADS; ++ptid)
			pthread_create(&pid1[ptid],NULL,thread_fun1,NULL);
		for (ctid = 0; ctid < cCANT_THREADS; ++ctid)
			pthread_create(&pid2[ctid],NULL,thread_fun2,NULL);
		for(ringpos=0;ringpos<N;ringpos++)
			printf("%d=%d-\n",ringpos,b[ringpos]);
	}

	

return 0;
}
