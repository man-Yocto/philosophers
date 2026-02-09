/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkhaso <aalkhaso@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 01:01:41 by aalkhaso          #+#    #+#             */
/*   Updated: 2026/02/10 01:01:53 by aalkhaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	d;

	if (init_all(&d, argc, argv))
		return (1);
	if (start_simu(&d))
	{
		cleanup(&d);
		return (1);
	}
	cleanup(&d);
	return (0);
}
