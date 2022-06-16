/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 10:24:23 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/06/16 12:19:22 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

long	get_time_now(void)
{
	struct timeval	time;
	int				ret;

	ret = gettimeofday(&time, NULL);
	if (ret == -1)
	{
		printf("gettimeday() failed\n");
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	better_sleep(int total_ms)
{
	long	begin;

	begin = get_time_now();
	while ((get_time_now() - begin) < total_ms)
		usleep(10);
}
