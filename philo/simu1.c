/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkhaso <aalkhaso@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 09:08:02 by aalkhaso          #+#    #+#             */
/*   Updated: 2026/02/12 09:28:24 by aalkhaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < data->n)
	{
		if (check_death(&data->philos[i]))
		{
			update_stop(data);
			print_died(data, data->philos[i].id + 1, "died");
			return (1);
		}
		if (check_meals(&data->philos[i]))
			count++;
		i++;
	}
	if (count >= data->n && data->must_eat != -1)
	{
		update_stop(data);
		usleep(10);
		return (1);
	}
	return (0);
}

void	update_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mtx);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mtx);
}

void	calc_think(t_philo *guest, long *think_time)
{
	pthread_mutex_lock(&guest->data->meal_mtx);
	*think_time = (guest->data->t_die - (get_time() - guest->last_meal)
			- guest->data->t_eat) / 2;
	pthread_mutex_unlock(&guest->data->meal_mtx);
	if (*think_time < 0)
		*think_time = 0;
	if (*think_time > 600)
		*think_time = 200;
}

void	initial_case(t_philo *guest)
{
	if (guest->id % 2 == 1)
	{
		print_stat(guest->data, guest->id + 1, "is thinking");
		usleep(guest->data->t_eat * 1000 / 2);
	}
}

int	check_case_one(t_data *data)
{
	if (data->n == 1)
	{
		case_one(&data->philos[0], 0);
		return (1);
	}
	return (0);
}
