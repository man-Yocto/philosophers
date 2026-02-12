/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkhaso <aalkhaso@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 01:00:07 by aalkhaso          #+#    #+#             */
/*   Updated: 2026/02/12 09:30:31 by aalkhaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
