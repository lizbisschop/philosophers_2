/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 15:23:59 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/22 13:43:21 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
#include <unistd.h>

//remove!!!
# include <errno.h>
# include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct s_table {
                long start_time;
                bool  *locked_forks;
                bool dead_bool;

                //threads
                pthread_t *threads;
                pthread_t dead;

                //mutexes
                pthread_mutex_t *forks;
                pthread_mutex_t last_eaten;
                pthread_mutex_t dead_mutex;
                pthread_mutex_t write;
}               t_table;

typedef struct s_philosopher {
                t_table *tab;
                int philo_id;
                int left_fork;
                int right_fork;
                int total_philos;
                int time_die;
                int time_eat;
                int time_sleep;
                int times_to_eat;
                int times_eaten;
                long last_time_eaten;
                long start_time;
                bool times_to_eat_bool;
                bool error_occured;          
}               t_philosopher;


typedef struct s_data {
    t_philosopher  *philos;
    t_table        table;
    int            total_philos;
    int start_time;
}               t_data;

//initilizing functions
void init_philos(int argc, char **argv, t_data *data);
void init_table(char **argv, t_data *data);

//threading function
void                threading(t_data *data);

//main things
void    *eat_sleep_think(void *p);
int exit_with_error(t_philosopher *philo, char *str);
void custom_print(t_philosopher *philo, char *str);
void *dead(void* d);
bool check_dead(t_philosopher *philo);

//utils functions
int	                ft_atoi(const char *str);
int	                is_number(char *str);
int	                is_digit(char c);
int	                ft_strncmp(char *str1, char *str2);
int	                ft_strlen(const char *str);
void                better_sleep(int total_ms);
long                get_time_now(void);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif