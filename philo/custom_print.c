/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   custom_print.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 14:36:08 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/06/16 15:18:08 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void custom_print(t_philosopher *philo, char *str)
{
    long time;
    
    time = get_time_now();
    if (pthread_mutex_lock(&philo->tab->write) != 0)
        exit_with_error("write lock failed");
    printf("%li %d %s\n", time - philo->tab->start_time, philo->philo_id, str);
    if (pthread_mutex_unlock(&philo->tab->write) != 0)
        exit_with_error("unlock lock failed");
}