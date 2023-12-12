#include "philosophers.h"

bool	alive(t_philos *philo)
{
	bool state = true;
	pthread_mutex_lock(philo->pcontrol);
	if (!philo->state) state = false;
	pthread_mutex_unlock(philo->pcontrol);
	return state;
}



void	*routine(void *ptr)
{
	t_philos *philos;
	
	philos = ((t_philos *)ptr);
	while (alive(philos))
	{
		;
	}
}

bool	philosophers_init(t_data *philosophers, void (*routine)())
{
	int i = 0;
	get_time();
	while(i < philosophers->params->philos_num)
	{
		if (pthread_create(philosophers->threads[i], NULL, routine, &philosophers->philos[i]))
			return false;
		i++;
	}
	return true;
}




