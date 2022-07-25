/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   custom_print.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 14:36:08 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/25 17:10:52 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

bool	custom_print(t_philosopher *philo, char *str)
{
	if (!ft_strnstr(str, "died", ft_strlen(str)))
	{		
		if (check_dead(philo) == true)
		{
			return (true);
		}
	}
	// pthread_mutex_lock(&philo->tab->dead_mutex);
	printf("%li %d %s\n", get_time_now() - philo->tab->start_time, philo->philo_id, str);
	// if (ft_strnstr(str, "eating", ft_strlen(str)))
		// printf(" %d", philo->times_eaten);
	// printf("\n");
	// pthread_mutex_unlock(&philo->tab->dead_mutex);
	return (false);
}
