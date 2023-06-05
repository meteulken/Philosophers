#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int balance = 0;

pthread_mutex_t mutex;


int read_balance()
{
	usleep(250000);
	return balance;
}

void write_balance(int new_balance)
{
	usleep(250000);
	balance = new_balance;
}

void* deposit(void *money)
{
	pthread_mutex_lock(&mutex);

	int account_balance = read_balance();
	
	account_balance += *((int *)money);

	write_balance(account_balance);
	
	pthread_mutex_unlock(&mutex);

	return NULL;
}

int main()
{
	int before = read_balance();
	printf("Before : %d\n",before);

	int para1 = 100;
	int para2 = 200;

	pthread_t thread1;
	pthread_t thread2;
	
	pthread_mutex_init(&mutex,NULL);

	pthread_create(&thread1,NULL,deposit,(void*)&para1);
	pthread_create(&thread2,NULL,deposit,(void*)&para2);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	pthread_mutex_destroy(&mutex);

	int after = read_balance();
	printf("After : %d\n",after);

	return 0;
}
