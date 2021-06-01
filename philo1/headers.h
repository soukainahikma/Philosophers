#ifndef HEADERS_H
#define HEADERS_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<pthread.h>
#include<semaphore.h>
#include <sys/time.h>

typedef struct s_philo
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_philo_must_eat;
	int				i;
	int				a;
	pthread_t		*tid;
	pthread_mutex_t	*lock;
	pthread_mutex_t	myfork;
	// pthread_mutex_t	died;

	struct timeval	start_eating;
	struct timeval	init;
	long			duration;
	// int				alive;
	pthread_mutex_t	life;
}				t_philo;

int				alive;

pthread_mutex_t	test_g;
pthread_mutex_t	g_print;
int		ft_atoi(const char *str);
void	printer(t_philo *philo);
void	table(t_philo *philo);
long get_duration(struct timeval start_tp);
long	get_time_milisecond(long sec, long usec);
void	lock_forks1(t_philo *philo,int i);
void	lock_forks2(t_philo *philo,int i);


#endif