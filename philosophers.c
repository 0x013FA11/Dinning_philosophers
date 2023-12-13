#include "philosophers.h"

bool	is_alive(t_philos *philo)
{
	bool state = true;
	pthread_mutex_lock(philo->pcontrol);
	if (!philo->state) state = false;
	pthread_mutex_unlock(philo->pcontrol);
	return state;
}
void	kill_philo(void *philo)
{
	pthread_mutex_lock(((t_philos *)philo)->pcontrol);
	((t_philos *)philo)->state = false;
	pthread_mutex_unlock(((t_philos *)philo)->pcontrol);
}

void	take_shopstick(void *philo)
{
	pthread_mutex_lock(((t_philos *)philo)->right_fork);
	printf("%lld %d %s\n", get_time(), ((t_philos *)philo)->id, SHOPSTICK);
	if (!is_alive((t_philos *)philo))
		return;
	pthread_mutex_lock(((t_philos *)philo)->left_fork);
	printf("%lld %d %s\n", get_time(), ((t_philos *)philo)->id, SHOPSTICK);

}

void	usleeep(void *philo, long long ms)
{
	long long start;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		if (!is_alive((t_philos *)philo))
			return;
		usleep(1000);
	}
}

void	eat(void *philo)
{
	long long start;

	start = get_time();
	printf("%lld %d %s\n", start, ((t_philos *)philo)->id, EAT);
	pthread_mutex_lock(((t_philos *)philo)->pcontrol);
	((t_philos *)philo)->last_meal = start;
	if (((t_philos *)philo)->params->time_must_eat >= 0)
	{
		((t_philos *)philo)->meal_times++;
		if (((t_philos *)philo)->meal_times == ((t_philos *)philo)->params->time_must_eat)
			((t_philos *)philo)->state = false;
	}
	pthread_mutex_unlock(((t_philos *)philo)->pcontrol);
	usleeep(philo, ((t_philos *)philo)->params->time_to_eat);
}

void	actions(void *philo, void (*act)(t_philos *))
{
	if (!is_alive((t_philos *)philo))
		return;
	act((t_philos *)philo);
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
	void (*act[4]) (t_philos);
	int i = 0;
	get_time();
	act = philosophers_actions();
	while(i < philosophers->params->philos_num)
	{
		if (pthread_create(philosophers->threads[i], NULL, routine, &philosophers->philos[i]))
			return false;
		i++;
	}
	return true;
}




