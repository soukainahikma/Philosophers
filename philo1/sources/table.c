#include "../headers.h"
void	get_food(t_philo *philo)
{
	struct timeval tp;
	pthread_mutex_lock(&philo->life);
	pthread_mutex_lock(&philo->lock[philo->i]);
	lock_msg(philo, FORK, 0);
	pthread_mutex_lock(&philo->lock[(philo->i + 1) % philo->number_of_philo]);
	lock_msg(philo, FORK, 0);
	gettimeofday(&tp, NULL);
	philo->start_eating = tp;
	lock_msg(philo, EAT, philo->time_to_eat);
	// if(alive == 1)
		// usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->lock[(philo->i + 1) % philo->number_of_philo]);
	pthread_mutex_unlock(&philo->lock[philo->i]);
	pthread_mutex_unlock(&philo->life);
}

void	think(t_philo *p)
{
	lock_msg(p, THINK, 0);
}

void	sleep_(t_philo *p)
{
		lock_msg(p, SLEEP, p->time_to_sleep);
		// if(alive == 1)
			// usleep(p->time_to_sleep * 1000);
}

void *death_check(void *philo)
{
	t_philo *p;
	p = (t_philo *)philo;

	while(alive == 1)
	{
		usleep(100);
		pthread_mutex_lock(&p->life);
		if(get_duration(p->start_eating) > p->time_to_die)
			lock_msg(p, DEAD, 0);
		pthread_mutex_unlock(&p->life);
	}
	return (NULL);
}

void	*philosopher(void *p)
{
	t_philo	*philo;
	pthread_t death_checker;
	struct timeval tp;

	philo = (t_philo *) p;
	gettimeofday(&tp , NULL);
	philo->start_eating = tp;
	pthread_mutex_init(&philo->life,NULL);
	pthread_create(&death_checker, NULL,death_check, philo);
	while (alive == 1)
	{	
		if (alive == 0)
			break ;
		get_food(philo);
		sleep_(philo);
		think(philo);
	}
	alive = 0;
	pthread_join(death_checker,NULL);
	pthread_mutex_destroy(&philo->life);
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
	p->start_eating = philo->start_eating;
	p->init = philo->init;
	p->duration = philo->duration;
	return (p);
}

void	table(t_philo *philosopher_)
{
	init_mutex(philosopher_);
	ft_creat_threads(philosopher_);
	ft_join_theads(philosopher_);
	ft_clear(philosopher_);
}
