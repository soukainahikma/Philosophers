#include "../headers.h"

void	get_food(t_philo *philo)
{
	struct timeval	tp;

	pthread_mutex_lock(&philo->lock[philo->i]);
	lock_msg(philo, FORK, 0);
	pthread_mutex_lock(&philo->lock[(philo->i + 1) % philo->number_of_philo]);
	lock_msg(philo, FORK, 0);
	gettimeofday(&tp, NULL);
	philo->start_eating = tp;
	pthread_mutex_lock(&philo->life);
	lock_msg(philo, EAT, philo->time_to_eat);
	if (philo->nb_philo_must_eat >= 0)
		philo->nb_philo_must_eat--;
	pthread_mutex_unlock(&philo->life);
	pthread_mutex_unlock(&philo->lock[(philo->i + 1) % philo->number_of_philo]);
	pthread_mutex_unlock(&philo->lock[philo->i]);
}

void	*death_check(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (p->var->alive == 1)
	{
		usleep(100);
		pthread_mutex_lock(&p->life);
		if (get_duration(p->start_eating) > p->time_to_die)
			lock_msg(p, DEAD, 0);
		pthread_mutex_unlock(&p->life);
	}
	return (NULL);
}

void	*philosopher(void *p)
{
	t_philo			*philo;
	pthread_t		death_checker;
	struct timeval	tp;

	philo = (t_philo *) p;
	gettimeofday(&tp, NULL);
	philo->start_eating = tp;
	pthread_mutex_init(&philo->life, NULL);
	pthread_create(&death_checker, NULL, death_check, philo);
	while (philo->var->alive == 1 && (philo->nb_philo_must_eat > 0
			|| philo->nb_philo_must_eat == -2))
	{
		get_food(philo);
		lock_msg(philo, SLEEP, philo->time_to_sleep);
		lock_msg(philo, THINK, 0);
	}
	pthread_join(death_checker, NULL);
	pthread_mutex_destroy(&philo->life);
	return (NULL);
}

t_philo	*get_struc(t_philo *philo, t_global_var *var)
{
	t_philo	*p;

	p = (t_philo *)malloc(sizeof(t_philo));
	p->var = var;
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
	t_global_var *var;

	var = (t_global_var*)malloc(sizeof(t_global_var));
	init_mutex(philosopher_, var);
	ft_creat_threads(philosopher_, var);
	ft_join_theads(philosopher_);
	ft_clear(philosopher_, var);
}
