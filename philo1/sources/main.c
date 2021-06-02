#include"../headers.h"

int	**dispatcher(t_philo *philo_)
{
	int	**philo;

	philo = malloc(sizeof(int *) * 5);
	philo[0] = &philo_->number_of_philo;
	philo[1] = &philo_->time_to_die;
	philo[2] = &philo_->time_to_eat;
	philo[3] = &philo_->time_to_sleep;
	philo[4] = &philo_->nb_philo_must_eat;
	return (philo);
}

void	ft_initializer(t_philo *philo)
{
	philo->number_of_philo = 0;
	philo->time_to_eat = 0;
	philo->time_to_die = 0;
	philo->time_to_sleep = 0;
	philo->nb_philo_must_eat = -2;
	philo->duration = 0;
}

int	main(int argc, char **argv)
{
	t_philo			philo;
	int				j;
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	philo.init = tp;
	j = 1;
	ft_initializer(&philo);
	if (argc == 5 || argc == 6)
	{
		while (argv[j])
		{
			*(dispatcher(&philo)[j - 1]) = ft_atoi(argv[j]);
			j++;
		}
	}
	philo.tid = malloc((sizeof(pthread_t) * philo.number_of_philo));
	philo.lock = malloc((sizeof(pthread_mutex_t) * philo.number_of_philo));
	table(&philo);
	return (0);
}
