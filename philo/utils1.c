/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkhaso <aalkhaso@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 09:10:03 by aalkhaso          #+#    #+#             */
/*   Updated: 2026/02/12 09:30:46 by aalkhaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	case_one(t_philo *guest, int left)
{
	t_data	*data;

	data = guest->data;
	pthread_mutex_lock(&data->forks[left]);
	print_stat(data, guest->id + 1, "has taken a fork");
	while (!check_stop(data))
		usleep(500);
	pthread_mutex_unlock(&data->forks[left]);
}

int	joinem(t_data *data)
{
	int	i;
	int	to;

	i = 0;
	if (data->stop)
		to = data->created;
	else
		to = data->n;
	while (i < to)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (1);
		i++;
	}
	if (data->monitor_thread && pthread_join(data->monitor_thread, NULL))
		return (1);
	return (0);
}

void	update_meal_t(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mtx);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meal_mtx);
}

void	inc_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mtx);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->data->meal_mtx);
}

void	cleanup(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->forks_initialized)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	if (data->print_mtx_initialized)
		pthread_mutex_destroy(&data->print_mtx);
	if (data->stop_mtx_initialized)
		pthread_mutex_destroy(&data->stop_mtx);
	if (data->meal_mtx_initialized)
		pthread_mutex_destroy(&data->meal_mtx);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}
