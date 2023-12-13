/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hano <sel-hano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:37:10 by sel-hano          #+#    #+#             */
/*   Updated: 2023/12/13 19:00:49 by sel-hano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_shopstick(void *philo)
{
	pthread_mutex_lock(((t_philos *)philo)->right_fork);
	if (!is_alive((t_philos *)philo))
	{
		pthread_mutex_unlock(((t_philos *)philo)->right_fork);
		return ;
	}
	printf("%lld %d %s\n", get_time(), ((t_philos *)philo)->id, SHOPSTICK);
	pthread_mutex_lock(((t_philos *)philo)->left_fork);
	if (!is_alive((t_philos *)philo))
	{
		pthread_mutex_unlock(((t_philos *)philo)->right_fork);
		return ;
	}
	printf("%lld %d %s\n", get_time(), ((t_philos *)philo)->id, SHOPSTICK);
}

void	eat(void *philo)
{
	long long	start;

	start = get_time();
	printf("%lld %d %s\n", start, ((t_philos *)philo)->id, EAT);
	pthread_mutex_lock(((t_philos *)philo)->pcontrol);
	((t_philos *)philo)->last_meal = start;
	if (((t_philos *)philo)->params->time_must_eat >= 0)
	{
		((t_philos *)philo)->meal_times++;
		if (((t_philos *)philo)->meal_times
			== ((t_philos *)philo)->params->time_must_eat)
			((t_philos *)philo)->state = false;
	}
	pthread_mutex_unlock(((t_philos *)philo)->pcontrol);
	usleeep(philo, ((t_philos *)philo)->params->time_to_eat);
}

void	sleep_and_think(void *philo)
{
	printf("%lld %d %s\n", get_time(), ((t_philos *)philo)->id, SLEEP);
	usleeep(philo, ((t_philos *)philo)->params->time_to_sleep);
	if (!is_alive((t_philos *)philo))
		return ;
	printf("%lld %d %s\n", get_time(), ((t_philos *)philo)->id, THINK);
	usleep(200);
}

void	actions(void *philo, void (*act)(void *))
{
	if (!is_alive((t_philos *)philo))
		return ;
	act((t_philos *)philo);
}

void	*routine(void *ptr)
{
	t_philos	*philos;

	philos = ((t_philos *)ptr);
	while (is_alive(philos))
	{
		actions(philos, take_shopstick);
		actions(philos, eat);
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		actions(philos, sleep_and_think);
	}
	return (NULL);
}
