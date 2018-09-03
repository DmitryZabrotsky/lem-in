#include "../lemin.h"

int is_int(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int parse_ants(char *s, t_farm *farm)
{
	if (!is_int(s))
		return (0);
	farm->ants = ft_atoi(s);
	if (farm->ants <= 0)
		return (0);
	return (1);
}

int stage_one(t_farm *farm)
{
	char *s;

	while (get_next_line(0, &s) > 0)
	{
		if (s[0] != '#')
			return (parse_ants(s, farm));
	}
	return (0);
}

void error_manager(int code, t_farm *farm)
{
	if (code == 0)
	{
		(void)farm;
		ft_putendl(RED "ERROR" RESET);
		//del_farm(farm);
		exit(1);
	}
}

int main(void)
{
	t_farm *farm;
	
	farm = new_farm();
	error_manager(stage_one(farm), farm);
	describe_farm(farm);
	//del_farm(farm);
}