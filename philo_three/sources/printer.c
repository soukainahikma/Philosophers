#include"../headers.h"

void	printer(t_philo *philo)
{
	printf("number_of_philosophers                     :-- %d --\n",
		philo->number_of_philo);
	printf("time_to_die                                :-- %d --\n",
		philo->time_to_die);
	printf("time_to_eat                                :-- %d --\n",
		philo->time_to_eat);
	printf("time_to_sleep                              :-- %d --\n",
		philo->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat :-- %d --\n",
		philo->must_eat);
}
