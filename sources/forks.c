#include "../headers.h"

void lock_forks1(t_philo *philo,int i)
{
    struct timeval tp;
    pthread_mutex_lock(&g_print);
	philo->duration = get_duration(philo->init);
	printf("%ld Philosopher %d has taken fork %d\n", get_duration(philo->init), i + 1, i + 1);
	pthread_mutex_unlock(&g_print);
}
void lock_forks2(t_philo *philo,int i)
{
    struct timeval tp;
    pthread_mutex_lock(&g_print);
	philo->duration = get_duration(philo->init);
	printf("%ld Philosopher %d has taken fork %d\n", philo->duration, i + 1 , (i + 1) % philo->number_of_philo +1);
	pthread_mutex_unlock(&g_print);
}