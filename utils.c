#include "philo.h"

int ft_atoi(char *str)
{
    int i = 0;
    int res = 0;
    int sign = 1;

    while(str[i] <= 32)
    {
        i++;
    }
    if (str[i] == '-')
    {
        sign *= -1;
        i++;
    }
    if(str[i] == '+')
    {
        i++;
    }

    while(str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    return (res * sign);
    
}


long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

long long	delta_time(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

void	exec_action(long long time)
{
	usleep(time * 1000);
}