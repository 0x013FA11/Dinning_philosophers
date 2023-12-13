#include "philosophers.h"


int main(int ac, char *av[])
{
	t_data data;
	t_params params;
	if (!parse_arguments(ac, av, &params,&data))
		return (printf("Error : %s", ERR), 1);
	if (!philosophers_init(&data, routine))
	{
		return 1;
	}
	else {
		int i = 0;
		while(i < params.philos_num)
		{
			if(pthread_join(data.threads[i], NULL))
				return 1;
			i++;	
		}
	}
	return 0;
}