/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkhaso <aalkhaso@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 00:59:20 by aalkhaso          #+#    #+#             */
/*   Updated: 2026/02/12 09:28:03 by aalkhaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simu(t_data *data)
{
	struct timeval	time;
	int				i;

	i = 0;
	gettimeofday(&time, NULL);
	data->start_time = get_time();
	while (i < data->n)
	{
		pthread_mutex_lock(&data->meal_mtx);
		data->philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->meal_mtx);
		if (pthread_create(&data->philos[i].thread, NULL, hotel,
				&data->philos[i]))
		{
			data->stop = 1;
			break ;
		}
		data->created++;
		i++;
	}
	if (pthread_create(&data->monitor_thread, NULL, room_service, data))
		data->stop = 1;
	if (joinem(data))
		return (1);
	return (0);
}

void	take_and_eat(t_philo *guest, int left, int right)
{
	t_data		*data;
	long long	end;

	data = guest->data;
	pthread_mutex_lock(&data->forks[get_min(left, right)]);
	print_stat(data, guest->id + 1, "has taken a fork");
	pthread_mutex_lock(&data->forks[get_max(left, right)]);
	print_stat(data, guest->id + 1, "has taken a fork");
	update_meal_t(guest);
	print_stat(data, guest->id + 1, "is eating");
	end = get_time() + data->t_eat;
	while (get_time() < end)
	{
		usleep(100);
		if (check_stop(data))
		{
			pthread_mutex_unlock(&data->forks[get_min(left, right)]);
			pthread_mutex_unlock(&data->forks[get_max(left, right)]);
			return ;
		}
	}
	pthread_mutex_unlock(&data->forks[get_min(left, right)]);
	pthread_mutex_unlock(&data->forks[get_max(left, right)]);
	inc_meal(guest);
}

void	philo_sleep(t_philo *guest)
{
	t_data		*data;
	long long	end;

	data = guest->data;
	print_stat(data, guest->id + 1, "is sleeping");
	end = get_time() + data->t_sleep;
	while (get_time() < end)
	{
		usleep(100);
		if (check_stop(data))
			return ;
	}
}

void	*hotel(void *arg)
{
	t_philo	*guest;
	t_data	*data;
	int		left;
	int		right;
	long	think_time;

	guest = (t_philo *)arg;
	data = guest->data;
	left = guest->id;
	right = (guest->id + 1) % data->n;
	initial_case(guest);
	while (!check_stop(data))
	{
		if (checkCaseOne(data))
			return (NULL);
		print_stat(data, guest->id + 1, "is thinking");
		calc_think(guest, &think_time);
		if (think_time > 0)
			usleep(think_time * 1000);
		if (check_stop(data))
			return (NULL);
		take_and_eat(guest, left, right);
		philo_sleep(guest);
	}
	return (NULL);
}

void	*room_service(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	while (!check_stop(data))
	{
		if (check_all(data))
			return (NULL);
		usleep(10);
	}
	return (NULL);
}