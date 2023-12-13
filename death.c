/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hano <sel-hano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:37:38 by sel-hano          #+#    #+#             */
/*   Updated: 2023/12/13 18:38:45 by sel-hano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	kill_philo(void *philo)
{
	pthread_mutex_lock(((t_philos *)philo)->pcontrol);
	((t_philos *)philo)->state = false;
	pthread_mutex_unlock(((t_philos *)philo)->pcontrol);
}

void	died(t_philos *philo, int i)
{
	int	x;

	x = -1;
	philo[i].state = false;
	printf("%lld %d %s", get_time(), philo[i].id, DEATH);
	while (++x < philo->params->philos_num)
	{
		if (x == i)
			continue ;
		kill_philo(philo + x);
	}
}

void	death_controler(t_data *data)
{
	int	flag;
	int	i;

	flag = 0;
	while (flag != data->params->philos_num)
	{
		flag = 0;
		i = 0;
		while (i < data->params->philos_num)
		{
			pthread_mutex_lock(data->philos[i].pcontrol);
			if (!data->philos[i].state)
				flag++;
			else if ((get_time()
					- data->philos[i].last_meal) >= data->params->time_to_die)
				died(data->philos, i);
			pthread_mutex_unlock(data->philos[i].pcontrol);
			i++;
		}
	}
}
