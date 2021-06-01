#include "../headers.h"

void lock_msg(t_philo *p, int id, int wait)
{
	pthread_mutex_lock(&g_print);
	if(alive == 1)
	{
		if(id == FORK && (p->nb_philo_must_eat > 0 || p->nb_philo_must_eat == -2))
			printf("%ld %d has taken fork\n", get_duration(p->init), p->i + 1);
		if(id == EAT)
			printf("%ld %d is eating\n", get_duration(p->init), p->i + 1);
		if(id == SLEEP && (p->nb_philo_must_eat > 0 || p->nb_philo_must_eat == -2))
			printf("%ld %d is sleeping\n", get_duration(p->init), p->i + 1);
		if(id == THINK && (p->nb_philo_must_eat > 0 || p->nb_philo_must_eat == -2))
			printf("%ld %d is thinking\n", get_duration(p->init), p->i + 1);
		if(id == DEAD)
		{
			if(p->nb_philo_must_eat > 0 || p->nb_philo_must_eat == -2)
				printf("%ld %d died\n", get_duration(p->init), p->i + 1);
			else
				printf("done\n");
			alive = 0;
		}
	}
	pthread_mutex_unlock(&g_print);
	if(alive == 1&& (p->nb_philo_must_eat > 0 || p->nb_philo_must_eat == -2))
		usleep(wait * 1000);
}