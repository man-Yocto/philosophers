/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkhaso <aalkhaso@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 01:00:07 by aalkhaso          #+#    #+#             */
/*   Updated: 2026/02/10 01:00:18 by aalkhaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->n)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mtx);
	pthread_mutex_destroy(&data->stop_mtx);
	pthread_mutex_destroy(&data->meal_mtx);
	if (data->philos)
		free(data->philos);
}
int	ft_posatoi(const char *nptr)
{
	size_t	i;
	int		result;

	i = 0;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			return (0);
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] != '\0')
		return (0);
	return (result);
}
long	ft_posatol(const char *nptr)
{
	size_t	i;
	long	result;

	i = 0;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			return (0);
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] != '\0')
		return (0);
	return (result);
}
void	print_stat(t_data *data, int id, char *msg)
{
	long	t;

	pthread_mutex_lock(&data->print_mtx);
	if (check_stop(data))
	{
		pthread_mutex_unlock(&data->print_mtx);
		return ;
	}
	t = get_time() - data->start_time;
	printf("%ld %d %s\n", t, id, msg);
	pthread_mutex_unlock(&data->print_mtx);
}

void	print_died(t_data *data, int id, char *msg)
{
	long	t;

	pthread_mutex_lock(&data->print_mtx);
	t = get_time() - data->start_time;
	printf("%ld %d %s\n", t, id, msg);
	pthread_mutex_unlock(&data->print_mtx);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

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