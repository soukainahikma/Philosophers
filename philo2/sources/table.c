#include "../headers.h"

void	get_food(t_philo *philo)
{
	struct timeval tp;
	sem_wait(philo->sem);
	lock_msg(philo, FORK, 0);

	sem_wait(philo->sem);
	lock_msg(philo, FORK, 0);
	gettimeofday(&tp, NULL);
	philo->start_eating = tp;
	sem_wait(philo->life);
	lock_msg(philo, EAT, philo->time_to_eat);
	if(philo->nb_philo_must_eat >= 0)
		philo->nb_philo_must_eat--;
	sem_post(philo->life);
	sem_post(philo->sem);
	sem_post(philo->sem);
}

void	think(t_philo *p)
{
	lock_msg(p, THINK, 0);
}

void	sleep_(t_philo *p)
{
		lock_msg(p, SLEEP, p->time_to_sleep);
}

void *death_check(void *philo)
{
	t_philo *p;
	p = (t_philo *)philo;

	while(alive == 1)
	{
		usleep(100);
		sem_wait(p->life);
		if(get_duration(p->start_eating) > p->time_to_die)
			lock_msg(p, DEAD, 0);
		sem_post(p->life);
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
	sem_unlink("/life");
	philo->life = sem_open("/life", O_CREAT, 0600, 1);
	pthread_create(&death_checker, NULL,death_check, philo);
	while (alive == 1 && (philo->nb_philo_must_eat > 0 || philo->nb_philo_must_eat == -2))
	{
		get_food(philo);
		sleep_(philo);
		think(philo);
	}
	pthread_join(death_checker,NULL);
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
	p->sem = philo->sem;
	p->start_eating = philo->start_eating;
	p->init = philo->init;
	p->duration = philo->duration;
	return (p);
}

void	table(t_philo *philosopher_)
{
	char *str="/wait_philo";
	//  sem_unlink(str);
	init_semaphore(philosopher_, str);
	ft_creat_threads(philosopher_);
	ft_join_theads(philosopher_);
	
	// ft_clear(philosopher_);
}
