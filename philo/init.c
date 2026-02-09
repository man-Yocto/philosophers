/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocto <yocto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:42:55 by yocto             #+#    #+#             */
/*   Updated: 2026/02/09 13:38:01 by yocto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int values_check(t_data *data, int argc, char **argv)
{
    data->n = ft_posatoi(argv[1]);
    data->t_die = ft_posatol(argv[2]);
    data->t_eat = ft_posatol(argv[3]);
    data->t_sleep = ft_posatol(argv[4]);
    if (argc == 6)
        data->must_eat = ft_posatoi(argv[5]);
    if (data->n <= 0 || data->t_die <= 0 || data->t_eat <= 0 || data->t_sleep <= 0)
        return (1);
    if (argc == 6 && data->must_eat <= 0)
        return (1);
    return (0);
}
int init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (!(data->forks = malloc(sizeof(pthread_mutex_t) * data->n)))
		return (1);
	while (i < data->n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
    if(pthread_mutex_init(&data -> print_mtx, NULL))
            return (1);
    if(pthread_mutex_init(&data -> stop_mtx, NULL))
            return (1);
    if(pthread_mutex_init(&data -> meal_mtx, NULL))
            return (1);
    return (0);
}
int init_philos(t_data *data)
{
    int i = 1;
    if(!(data->philos = malloc(sizeof(t_philo) * data -> n)))
        return (1);
    while(i < data->n + 1)
    {
        data->philos[i-1].id = i - 1;
        data->philos[i-1].meals_eaten = 0;
        data->philos[i-1].last_meal = 0;
        data->philos[i-1].left_fork = &data->forks[i - 1];
        data->philos[i-1].right_fork = &data->forks[i % data->n];
        data->philos[i-1].data = data;
        i++;
    }
    return (0);
}
int init_all(t_data *data, int argc, char **argv)
{
    if (argc != 5 && argc != 6)
        return (1);
    data ->stop = 0;
    data->must_eat = -1;
    data->created = 0;
    if(values_check(data, argc, argv))
        return (1);
    if(init_mutexes(data))
        return (1);
    if(init_philos(data)){
        cleanup(data);  
        return (1);
    }

    return (0); 
}
