#include "philosophers.h"

int	main(int ac, char *av[])
{
	t_data		data;
	t_params	params;
	int			i;

	if (!parse_arguments(ac, av, &params, &data))
		return (printf("Error : %s", ERR), 1);
	if (!philosophers_init(&data, routine))
		return (1);
	controler(&data);
	i = 0;
	if (params.philos_num == 1)
		pthread_detach(*(data.threads));
	while (i < params.philos_num && params.philos_num > 1)
	{
		if (pthread_join(data.threads[i], NULL))
			return (1);
		i++;
	}
	return (free(data.philos), free(data.forks), free(data.control),free(data.threads), 0);
}
