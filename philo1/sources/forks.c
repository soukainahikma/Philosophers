#include "../headers.h"

void lock_msg(t_philo *p, int id, int wait)
{
	pthread_mutex_lock(&g_print);
	if(alive == 1)
	{
		if(id == FORK)
			printf("%ld %d has taken fork\n", get_duration(p->init), p->i + 1);
		if(id == EAT)
			printf("%ld %d is eating\n", get_duration(p->init), p->i + 1);
		if(id == SLEEP)
			printf("%ld %d is sleeping\n", get_duration(p->init), p->i + 1);
		if(id == THINK)
			printf("%ld %d is thinking\n", get_duration(p->init), p->i + 1);
		if(id == DEAD)
		{
			printf("%ld %d died\n", get_duration(p->init), p->i + 1);
			alive = 0;
		}
	}
	pthread_mutex_unlock(&g_print);
	if(alive == 1)
		usleep(wait * 1000);
}