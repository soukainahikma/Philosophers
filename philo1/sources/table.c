#include "../headers.h"
void	eat(t_philo *philo)
{
	struct timeval tp;
	if (alive == 1)
	{
		pthread_mutex_lock(&philo->life);
		pthread_mutex_lock(&philo->lock[philo->i]);
		if (alive == 1)
			lock_forks1(philo, philo->i);
		pthread_mutex_lock(&philo->lock[(philo->i + 1) % philo->number_of_philo]);
		if (alive == 1)
			lock_forks2(philo, philo->i);
		gettimeofday(&tp, NULL);
		philo->start_eating = tp;
		if (alive == 1)
		{
			pthread_mutex_lock(&g_print);
			philo->duration = get_duration(philo->init);
			// if(philo->nb_philo_must_eat != -2)
				// philo->nb_philo_must_eat--;
			printf("%ld %d is eating\n", philo->duration , philo->i + 1);
			pthread_mutex_unlock(&g_print);
		usleep(philo->time_to_eat * 1000);
		}
		pthread_mutex_unlock(&philo->lock[(philo->i + 1) % philo->number_of_philo]);
		pthread_mutex_unlock(&philo->lock[philo->i]);
		pthread_mutex_unlock(&philo->life);
	}
}

void	think(t_philo *p)
{
	if (alive == 1)
	{
		pthread_mutex_lock(&g_print);
		p->duration = get_duration(p->init);
		printf("%ld %d is thinking\n", p->duration, p->i + 1);
		pthread_mutex_unlock(&g_print);
	}
}

void	sleep_(t_philo *p)
{
	if (alive == 1)
	{
		pthread_mutex_lock(&g_print);
		p->duration = get_duration(p->init);
		printf("%ld %d is sleeping\n",p->duration, p->i + 1);
		pthread_mutex_unlock(&g_print);
		usleep(p->time_to_sleep * 1000);
	}
}
void *death_check(void *philo)
{
	t_philo *p;
	p = (t_philo *)philo;

	usleep(100);
	while(alive == 1)
	{
		pthread_mutex_lock(&p->life);
		if(get_duration(p->start_eating) > p->time_to_die/*  && alive */)
		{
			pthread_mutex_lock(&g_print);
			if(alive == 1)
			{
				printf("%ld %d died %d \n",get_duration(p->start_eating), p->i + 1,alive);
				alive = 0;
			}
			pthread_mutex_unlock(&g_print);
		}
		pthread_mutex_unlock(&p->life);
	}
	return (NULL);
}

void	*philosopher(void *philo)
{
	t_philo	*test;
	int		phil;
	pthread_t death_checker;
	struct timeval tp;
	test = (t_philo *) philo;

	
	gettimeofday(&tp , NULL);
	test->start_eating = tp;
	pthread_create(&death_checker, NULL,death_check, test);
	while (alive == 1)
	{	
		if (alive == 0)
			break ;
		eat(test);
		sleep_(test);
		think(test);
	}
	alive = 0;
	pthread_join(death_checker,NULL);
	pthread_mutex_destroy(&test->life);
	return (NULL);
}

t_philo *get_struc(t_philo *philo)
{
	t_philo *p;

	p = (t_philo *)malloc(sizeof(t_philo));
	p->number_of_philo = philo->number_of_philo;
	p->time_to_die = philo->time_to_die;
	p->time_to_eat = philo->time_to_eat;
	p->time_to_sleep = philo->time_to_sleep;
	p->nb_philo_must_eat = philo->nb_philo_must_eat;
	p->i = philo->i;
	p->tid = philo->tid;
	p->lock = philo->lock;
	p->myfork = philo->myfork;
	p->start_eating = philo->start_eating;
	p->init = philo->init;
	p->duration = philo->duration;
	return (p);
}

void	table(t_philo *phill)
{
	alive = 1;
	phill->i = 0;
	pthread_mutex_init(&g_print, NULL);
	while (phill->i < phill->number_of_philo)
	{
		pthread_mutex_init(&phill->lock[phill->i], NULL);
		phill->i++;
	}
	phill->i = 0;
	while (phill->i < phill->number_of_philo)
	{
		phill->a = phill->i;
		pthread_create(&phill->tid[phill->i], NULL, philosopher, (void *)get_struc(phill));
		usleep(100);
		phill->i++;
	}
	phill->i = 0;
	while (phill->i < phill->number_of_philo)
	{
		pthread_join(phill->tid[phill->i],NULL);
		phill->i++;
	}
	phill->i = 0;
	pthread_mutex_destroy(&g_print);
	while(phill->i < phill->number_of_philo)
	{
		pthread_mutex_destroy(&phill->lock[phill->i]);
		phill->i++;
	}
}
