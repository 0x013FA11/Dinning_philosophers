#include "philosophers.h"

long long	get_time(void)
{
	struct timeval res;
	static long long start;

	gettimeofday(&res, NULL);
	if (!start)
		start = res.tv_sec * 1000 - res.tv_usec / 1000;
	return ((res.tv_sec * 1000 - res.tv_usec / 1000) - start);
}