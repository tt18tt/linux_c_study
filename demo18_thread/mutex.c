/*
2020-6-3 22点10分
演示多个线程访问临界区导致错误的问题
通过mutex来解决线程同步的问题
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREAD	100

void *thread_inc(void* arg);
void *thread_des(void *arg);

long long num = 0;
pthread_mutex_t mutex;

int main()
{
	pthread_t thread_id[NUM_THREAD];
	int i;

	//对互斥量进行初始化
	pthread_mutex_init(&mutex, NULL);

	printf("sizeof long long: %d\n", sizeof(long long));
	for (i=0; i<NUM_THREAD; i++)
	{
		if (i%2)
		{
			pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
		}
		else
		{
			pthread_create(&(thread_id[i]), NULL, thread_des, NULL);
		}
	}

	for (i=0; i<NUM_THREAD; i++)
	{
		pthread_join(thread_id[i], NULL);
	}

	printf("result: %ld \n", num);

	//销毁互斥量
	pthread_mutex_destroy(&mutex);
	
	return 0;
}

void *thread_inc(void* arg)
{
	int i;
	pthread_mutex_lock(&mutex);		//这里放到循环外 是因为最大限度减少lock和unlock的调用次数
	for (i=0; i<50000000; i++)
	{
		num += 1;
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *thread_des(void *arg)
{
	int i;
	pthread_mutex_lock(&mutex);
	for (i=0; i<50000000; i++)
	{
		num -=1;
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}
