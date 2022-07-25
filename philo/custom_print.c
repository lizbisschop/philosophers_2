/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   custom_print.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 14:36:08 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/25 14:00:47 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	custom_print(t_philosopher *philo, char *str)
{
	pthread_mutex_lock(&philo->tab->write);
	printf("%li %d %s", get_time_now() - philo->tab->start_time, philo->philo_id, str);
	if (ft_strnstr(str, "eating", ft_strlen(str)))
		printf(" %d", philo->times_eaten);
	printf("\n");
	pthread_mutex_unlock(&philo->tab->write);
}
