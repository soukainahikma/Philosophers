#ifndef HEADERS_H
# define HEADERS_H
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DEAD 5
# define DONE 6
# include<stdio.h>
# include<string.h>
# include<stdlib.h>
# include<unistd.h>
# include<limits.h>
# include<pthread.h>
# include<semaphore.h>
# include<sys/time.h>

typedef struct s_global_var
{
	int				alive;
	pthread_mutex_t	g_print;
}				t_global_var;

typedef struct s_philo
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				i;
	int				a;
	pthread_t		*tid;
	pthread_mutex_t	*lock;
	struct timeval	start_eating;
	struct timeval	init;
	long			duration;
	pthread_mutex_t	life;
	t_global_var	*var;
}				t_philo;

int				ft_atoi(const char *str);
void			printer(t_philo *philo);
void			table(t_philo *philo);
long			get_duration(struct timeval start_tp);
long			get_time_milisecond(long sec, long usec);
void			*philosopher(void *philo);
t_philo			*get_struc(t_philo *philo, t_global_var *var);
void			init_mutex(t_philo *p, t_global_var *var);
void			ft_creat_threads(t_philo *p, t_global_var *var);
void			ft_join_theads(t_philo *p);
void			ft_clear(t_philo *p, t_global_var *var);
void			lock_msg(t_philo *p, int id, int wait);
int				ft_isdigit(int c);

#endif