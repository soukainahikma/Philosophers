#include "../headers.h"
void	eat(t_philo *philo)
{
	struct timeval tp;
	pthread_mutex_lock(&philo->lock[philo->i]);
	lock_forks1(philo, philo->i);
	pthread_mutex_lock(&philo->lock[(philo->i + 1) % philo->number_of_philo]);
	lock_forks2(philo, philo->i);
	gettimeofday(&tp, NULL);
	philo->start_eating = tp;
	pthread_mutex_lock(&g_print);
	philo->duration = get_duration(philo->init);
	if(philo->nb_philo_must_eat != -2)
		philo->nb_philo_must_eat--;
	printf("%ld %d is eating\n", philo->duration , philo->i + 1);
	pthread_mutex_unlock(&g_print);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->lock[(philo->i + 1) % philo->number_of_philo]);
	pthread_mutex_unlock(&philo->lock[philo->i]);
}

void	think(t_philo *p)
{
	pthread_mutex_lock(&g_print);
	p->duration = get_duration(p->init);
	printf("%ld Philosopher %d is thinking\n", p->duration, p->i + 1);
	pthread_mutex_unlock(&g_print);
}

void	sleep_(t_philo *p)
{
	pthread_mutex_lock(&g_print);
	p->duration = get_duration(p->init);
	printf("%ld %d is sleeping\n",p->duration, p->i + 1);
	pthread_mutex_unlock(&g_print);
	usleep(p->time_to_sleep * 1000);
}
void *death_check(void *philo)
{
	t_philo *p;
	p = (t_philo *)philo;

	while(1)
	{
		if(get_duration(p->start_eating) > p->time_to_die)
		{
			pthread_mutex_lock(&g_print);
			pthread_mutex_unlock(&test_g);
			if(p->nb_philo_must_eat > 0 || p->nb_philo_must_eat == -2)
				printf("%ld %d died\n",get_duration(p->start_eating), p->i + 1);
			break;
		}
		usleep(1000);
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
	pthread_detach(death_checker);
	while (1)
	{
		if(test->nb_philo_must_eat > 0 || test->nb_philo_must_eat == -2)
		{
			eat(test);
			sleep_(test);
			think(test);
		}
	}
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
	p->a = philo->a;
	p->tid = philo->tid;
	p->lock = philo->lock;
	p->myfork = philo->myfork;
	p->start_eating = philo->start_eating;
	p->init = philo->init;
	p->duration = philo->duration;
	p->life = philo->life;
	return (p);
}

void	table(t_philo *phill)
{
	phill->i = 0;
	// n_g = phill->
	pthread_mutex_init(&test_g, NULL);
	pthread_mutex_init(&g_print, NULL);
	while (phill->i < phill->number_of_philo)
	{
		pthread_mutex_init(&phill->lock[phill->i], NULL);
		phill->i++;
	}
	phill->i = 0;
	pthread_mutex_lock(&test_g);
	while (phill->i < phill->number_of_philo)
	{
		phill->a = phill->i;
		pthread_create(&phill->tid[phill->i], NULL, philosopher, (void *)get_struc(phill));
		pthread_detach(phill->tid[phill->i]);
		usleep(100);
		phill->i++;
	}
	pthread_mutex_lock(&test_g);
	pthread_mutex_unlock(&test_g);
}
