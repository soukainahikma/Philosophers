#include "../headers.h"

void	lock_msg(t_philo *p, int id, int wait)
{
	sem_wait(p->var->g_print);
	if (p->var->alive == 1)
	{
		if (id == FORK && (p->must_eat > 0 || p->must_eat == -2))
			printf("%ld %d has taken fork\n", get_duration(p->init), p->i + 1);
		if (id == EAT)
			printf("%ld %d is eating\n", get_duration(p->init), p->i + 1);
		if (id == SLEEP && (p->must_eat > 0 || p->must_eat == -2))
			printf("%ld %d is sleeping\n", get_duration(p->init), p->i + 1);
		if (id == THINK && (p->must_eat > 0 || p->must_eat == -2))
			printf("%ld %d is thinking\n", get_duration(p->init), p->i + 1);
		if (id == DEAD)
		{
			if (p->must_eat > 0 || p->must_eat == -2)
				printf("%ld %d died\n", get_duration(p->init), p->i + 1);
			else
				printf("done\n");
			p->var->alive = 0;
		}
	}
	sem_post(p->var->g_print);
	if (p->var->alive == 1 && (p->must_eat > 0 || p->must_eat == -2))
		usleep(wait * 1000);
}
