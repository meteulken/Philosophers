int max_number(int ac, char **av)
{
	if(unsigned_atoi(av[2]) > 200)
		return (err_msg("Max number.\n"));
	if(unsigned_atoi(av[3]) < 60 && unsigned_atoi(av[4]) < 60)
	    return (err_msg("Max number.\n"));
	return (1);
}

t_table	*parse(int ac, char **av)
{
	t_table	*table;

	if (!valid_check(ac, av))
		return (NULL);
	if (!max_number(ac,av))
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->number_of_philos = unsigned_atoi(av[1]);
	table->time_to_die = unsigned_atoi(av[2]);
	table->time_to_eat = unsigned_atoi(av[3]);
	table->time_to_sleep = unsigned_atoi(av[4]);
	table->number_of_must_eat = -1;
	if (ac == 6)
		table->number_of_must_eat = unsigned_atoi(av[5]);
	table->philos = malloc(sizeof(t_philo) * table->number_of_philos);
	table->time = current_time();
	table->stop = 0;
	return (table);
}
