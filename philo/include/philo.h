/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 15:23:59 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/08/03 12:55:04 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>

# define FAIL -1
# define SUCCESS 1

typedef struct s_table {
	long			start_time;
	bool			*locked_forks;
	bool			dead_bool;
	pthread_t		*threads;
	pthread_t		dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	last_eaten;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	write;
	pthread_mutex_t	starting;
}	t_table;

typedef struct s_philosopher {
	t_table	*tab;
	int		philo_id;
	int		left_fork;
	int		right_fork;
	int		total_philos;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		times_to_eat;
	int		times_eaten;
	long	last_time_eaten;
	bool	times_to_eat_bool;
	bool	error_occured;
}	t_philosopher;

typedef struct s_data {
	t_philosopher	*philos;
	t_table			table;
	int				total_philos;
}	t_data;

int		init_philos(int argc, char **argv, t_data *data);
int		init_table(char **argv, t_data *data);
int		threading(t_data *data);
void	*eat_sleep_think(void *p);
int		handle_error(char *str);
bool	custom_print(t_philosopher *philo, char *str);
void	*dead(void *d);
bool	check_dead(t_philosopher *philo);
int		ft_atoi(const char *str);
int		is_number(char *str);
int		is_digit(char c);
int		ft_strncmp(char *str1, char *str2);
int		ft_strlen(const char *str);
bool	better_sleep(int total_ms, t_philosopher *philo);
long	get_time_now(void);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif