/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   custom_print.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 14:36:08 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/23 13:27:35 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	custom_print(t_philosopher *philo, char *str)
{
	long	time;

	time = get_time_now();
	pthread_mutex_lock(&philo->tab->write);
	printf("%li %d %s", time - philo->tab->start_time, philo->philo_id, str);
	if (ft_strnstr(str, "eating", ft_strlen(str)))
		printf(" %d", philo->times_eaten);
	printf("\n");
	pthread_mutex_unlock(&philo->tab->write);
}
