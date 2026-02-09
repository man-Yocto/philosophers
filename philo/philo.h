/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocto <yocto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 23:47:54 by yocto             #+#    #+#             */
/*   Updated: 2026/02/09 17:07:33 by yocto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
	
typedef struct s_data	t_data;


typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data	*data;
}	t_philo;

typedef struct s_data
{
	int				n;
	int				created;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				must_eat;
	long			start_time;
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	stop_mtx;
	pthread_mutex_t	meal_mtx;
	t_philo			*philos;
	pthread_t		monitor_thread;
}	t_data;

void	*room_service(void *arg);
void	*hotel(void *arg);
int		joinem(t_data *data);
int		start_simu(t_data *data);
int check_death(t_philo *philo);
int check_meals(t_philo *philo);
void cleanup(t_data *data);
long	ft_posatol(const char *nptr);
int	ft_posatoi(const char *nptr);
long get_time();
void print_stat(t_data *data, int id, char *msg);
int get_min(int a, int b);
int get_max(int a, int b);
int check_stop(t_data *data);
void update_meal_t(t_philo *philo);
void inc_meal(t_philo *philo);
int init_all(t_data *data, int argc, char **argv);
int init_philos(t_data *data);
int init_mutexes(t_data *data);
int values_check(t_data *data, int argc, char **argv);
void print_died(t_data *data, int id, char *msg);
void case_one(t_philo *guest, int left);
void take_and_eat(t_philo *guest, int left, int right);
void philo_sleep(t_philo *guest);


    


#endif
