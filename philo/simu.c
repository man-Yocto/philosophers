/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkhaso <aalkhaso@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 00:59:20 by aalkhaso          #+#    #+#             */
/*   Updated: 2026/02/10 00:59:38 by aalkhaso         ###   ########.fr       */
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

int	checkCaseOne(t_data *data)
{
	if (data->n == 1)
	{
		case_one(&data->philos[0], 0);
		return (1);
	}
	return (0);
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

void	update_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mtx);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mtx);
}

static int	check_all(t_data *data)
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

void	*room_service(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!check_stop(data))
	{
		if (check_all(data))
			return (NULL);
		usleep(10);
	}
	return (NULL);
}