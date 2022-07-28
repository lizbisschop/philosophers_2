/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   custom_print.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 14:36:08 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/28 13:54:18 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

bool	custom_print(t_philosopher *philo, char *str)
{
	if (!ft_strnstr(str, "died", ft_strlen(str)))
	{		
		if (check_dead(philo) == true)
			return (true);
	}
	pthread_mutex_lock(&philo->tab->write);
	printf("%li %d %s\n", get_time_now()
		- philo->tab->start_time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->tab->write);
	return (false);
}
