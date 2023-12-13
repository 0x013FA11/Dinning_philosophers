/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hano <sel-hano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:56:28 by sel-hano          #+#    #+#             */
/*   Updated: 2023/12/13 18:57:37 by sel-hano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	long int	result;
	int			sign;

	result = 0;
	sign = 1;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-' && (*str >= '0' && *str <= '9'))
		str++;
	while ((*str >= '0' && *str <= '9'))
	{
		if (result > 2147483648 && sign < 0)
			return (-1);
		else if (result > 2147483647)
			return (-1);
		result = result * 10 + (*(str++) - 48);
	}
	if (*str)
		return (-1);
	return (result * sign);
}

int	check_params(t_params *params)
{
	if (params->philos_num <= 0 || params->time_must_eat < 0
		|| params->time_to_eat <= 0 || params->time_to_sleep <= 0
		|| params->time_to_die <= 0)
		return (0);
	return (1);
}

int	parse_arguments(int ac, char *av[], t_params *params, t_data *to_fill)
{
	if (ac == 5 || ac == 6)
	{
		params->philos_num = ft_atoi(av[1]);
		params->time_to_die = ft_atoi(av[2]);
		params->time_to_eat = ft_atoi(av[3]);
		params->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			params->time_must_eat = ft_atoi(av[5]);
		else
			params->time_must_eat = 0;
		if (check_params(params) == 1)
		{
			to_fill->params = params;
			if (initialize(to_fill))
				return (true);
		}
	}
	return (false);
}

bool	init_locks(t_data *init)
{
	int	i;

	init->threads = malloc(sizeof(pthread_t) * init->params->philos_num);
	if (!init->threads)
		return (false);
	init->philos = malloc(sizeof(t_philos) * init->params->philos_num);
	if (!init->philos)
		return (free(init->threads), false);
	init->forks = malloc(sizeof(pthread_mutex_t) * init->params->philos_num);
	if (!init->forks)
		return (free(init->philos), free(init->threads), false);
	init->control = malloc(sizeof(pthread_mutex_t) * init->params->philos_num);
	if (!init->control)
		return (free(init->forks), free(init->philos), free(init->threads),
			false);
	i = 0;
	while (i < init->params->philos_num)
	{
		if (pthread_mutex_init(&init->forks[i], NULL))
			return (false);
		if (pthread_mutex_init(&init->control[i], NULL))
			return (false);
		i++;
	}
	return (true);
}

bool	initialize(t_data *init)
{
	int	i;

	i = -1;
	if (!init_locks(init))
		return (false);
	while (++i < init->params->philos_num)
	{
		init->philos[i].id = i + 1;
		init->philos[i].right_fork = &init->forks[i];
		init->philos[i].left_fork = &init->forks[(i + 1)
			% init->params->philos_num];
		if (i % 2)
		{
			init->philos[i].right_fork = &init->forks[(i + 1)
				% init->params->philos_num];
			init->philos[i].left_fork = &init->forks[i];
		}
		init->philos[i].pcontrol = &init->control[i];
		init->philos[i].last_meal = 0;
		init->philos[i].meal_times = 0;
		init->philos[i].params = init->params;
		init->philos[i].state = true;
	}
	return (true);
}
