/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkhaso <aalkhaso@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 09:12:15 by aalkhaso          #+#    #+#             */
/*   Updated: 2026/02/12 09:31:03 by aalkhaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	check_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_mtx);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_mtx);
	return (stop);
}

void	initial_data(t_data *data)
{
	data->forks_initialized = 0;
	data->print_mtx_initialized = 0;
	data->stop_mtx_initialized = 0;
	data->meal_mtx_initialized = 0;
}
