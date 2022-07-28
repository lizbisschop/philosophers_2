/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 10:24:23 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/28 17:15:55 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && (i + j) <= len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
	}
	return (0);
}

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

bool	better_sleep(int total_ms, t_philosopher *philo)
{
	long	begin;
	int		i;

	i = 0;
	begin = get_time_now();
	while ((get_time_now() - begin) < total_ms)
	{
		if (i % 10000 == 0)
		{
			if (check_dead(philo))
				return (false);
		}
		usleep(250);
	}
	(void)philo;
	return (true);
}
