#include"../headers.h"

int	**dispatcher(t_philo *philo_, int **tap)
{
	tap[0] = &philo_->number_of_philo;
	tap[1] = &philo_->time_to_die;
	tap[2] = &philo_->time_to_eat;
	tap[3] = &philo_->time_to_sleep;
	tap[4] = &philo_->must_eat;
	return (tap);
}

void	ft_initializer(t_philo *philo)
{
	philo->number_of_philo = 0;
	philo->time_to_eat = 0;
	philo->time_to_die = 0;
	philo->time_to_sleep = 0;
	philo->must_eat = -2;
	philo->duration = 0;
}

int	check_arg(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '+' || argv[i] == '-')
		i++;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 0)
		{
			printf("%s is not a number\n", argv);
			return (-1);
		}
		i++;
	}
	if (argv[0] == '-')
	{
		printf("%s is a negative value\n", argv);
		return (-1);
	}
	return (0);
}

int	fill_args(int argc, char **argv, int **tab, t_philo *philo)
{
	int	j;

	j = 1;
	if (argc == 5 || argc == 6)
	{
		while (argv[j])
		{
			if (check_arg(argv[j]) == -1)
				return (0);
			*(dispatcher(philo, tab)[j - 1]) = ft_atoi(argv[j]);
			j++;
		}
	}
	else
	{
		printf("wrong number of parametres !\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo			philo;
	struct timeval	tp;
	int				**tab;

	tab = malloc(sizeof(int *) * 5);
	gettimeofday(&tp, NULL);
	philo.init = tp;
	ft_initializer(&philo);
	if (fill_args(argc, argv, tab, &philo) == 0)
		return (0);
	philo.tid = malloc((sizeof(pthread_t) * philo.number_of_philo));
	philo.lock = malloc((sizeof(pthread_mutex_t) * philo.number_of_philo));
	table(&philo);
	return (0);
}
