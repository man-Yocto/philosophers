/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocto <yocto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 23:48:04 by yocto             #+#    #+#             */
/*   Updated: 2026/02/01 02:51:57 by yocto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data d;

    if (init_all(&d, argc, argv))
        return (1);
    if(start_simu(&d))
    {
        cleanup(&d);
        return (1);
    }

    cleanup(&d);
    return (0);
}
