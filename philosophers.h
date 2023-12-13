#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define THINK "\033[1;32m is thinking\033[0m"
# define EAT "\033[2;80mis eating\033[0m"
# define SLEEP "\033[1;33m is sleeping\033[0m"
# define DEATH "\033[1;31m died\033[0m"
# define SHOPSTICK "\033[1;36m has taken a fork\033[0m"
# define PHILO_NUM \
	("\033[1;91m There has to be at least 1\
 philosopher\033[0m")
# define ONLY_DIGIT \
	("\033[1;91m Arguments have to be represented as\
 digits\033[0m")
# define SIZE_MATTERS
# define ERR "./philo NumberPhilos TimeToDie TimeToEat TimeToSleep EachTimeMustEat (optional)"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_param
{
	int				philos_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_must_eat;
}					t_params;

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				meal_times;
	bool			state;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*pcontrol;
	t_params		*params;
}					t_philos;

typedef struct s_data
{
	t_params		*params;
	t_philos		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*control;
	pthread_t		*threads;
}					t_data;

/*routine*/
void				*routine(void *ptr);
/*time*/
long long			get_time(void);
/*control*/
bool				philosophers_init(t_data *philosophers,
						void *(*routine)(void *));
void				controler(t_data *data);
/*parsing*/
int					parse_arguments(int ac, char *av[], t_params *params,
						t_data *to_fill);
bool				initialize(t_data *init);

#endif