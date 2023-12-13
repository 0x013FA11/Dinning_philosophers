/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hano <sel-hano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:37:28 by sel-hano          #+#    #+#             */
/*   Updated: 2023/12/13 19:00:14 by sel-hano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philosophers_init(t_data *philosophers, void *(*routine)(void *))
{
	int	i;

	i = 0;
	get_time();
	while (i < philosophers->params->philos_num)
	{
		if (pthread_create(&philosophers->threads[i], NULL, routine,
				&philosophers->philos[i]))
			return (false);
		i++;
	}
	return (true);
}

long long	get_time(void)
{
	struct timeval		res;
	static long long	start;

	gettimeofday(&res, NULL);
	if (!start)
		start = res.tv_sec * 1000 + res.tv_usec / 1000;
	return ((res.tv_sec * 1000 + res.tv_usec / 1000) - start);
}

void	usleeep(void *philo, long long ms)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		if (!is_alive((t_philos *)philo))
			return ;
		usleep(1000);
	}
}

bool	is_alive(t_philos *philo)
{
	bool	state;

	state = true;
	pthread_mutex_lock(philo->pcontrol);
	if (!philo->state)
		state = false;
	pthread_mutex_unlock(philo->pcontrol);
	return (state);
}
