/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkhaso <aalkhaso@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:41:47 by yocto             #+#    #+#             */
/*   Updated: 2026/02/12 09:27:24 by aalkhaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	int	ans;

	pthread_mutex_lock(&philo->data->meal_mtx);
	if (get_time() < philo->last_meal + philo->data->t_die)
		ans = 0;
	else
		ans = 1;
	pthread_mutex_unlock(&philo->data->meal_mtx);
	return (ans);
}

int	check_meals(t_philo *philo)
{
	int	ans;

	pthread_mutex_lock(&philo->data->meal_mtx);
	if (philo->data->must_eat == -1)
		ans = 0;
	else if (philo->meals_eaten >= philo->data->must_eat)
		ans = 1;
	else
		ans = 0;
	pthread_mutex_unlock(&philo->data->meal_mtx);
	return (ans);
}
