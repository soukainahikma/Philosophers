#include "../headers.h"

void	init_semaphore(t_philo *p, char *str, t_global_var *var)
{
	var->alive = 1;
	p->i = 0;
	sem_unlink("/print");
	var->g_print = sem_open("/print", O_CREAT, 0600, 1);
	sem_unlink(str);
	p->sem = sem_open(str, O_CREAT, 0600, p->number_of_philo);
}

void	ft_creat_threads(t_philo *p, t_global_var *var)
{
	p->i = 0;
	while (p->i < p->number_of_philo)
	{
		p->a = p->i;
		pthread_create(&p->tid[p->i], NULL,
			philosopher, (void *)get_struc(p, var));
		usleep(100);
		p->i++;
	}
}

void	ft_join_theads(t_philo *p)
{
	p->i = 0;
	while (p->i < p->number_of_philo)
	{
		pthread_join(p->tid[p->i], NULL);
		p->i++;
	}
}
