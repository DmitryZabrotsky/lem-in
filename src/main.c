#include "../lemin.h"

int			read_value(char *str, int i)
{
	char **arr;
	int res;

	arr = ft_strsplit(str, ' ');
	res = ft_atoi(arr[i]);
	ft_arrfree(&arr);
	return (res);
}

int			main(void)
{
	t_farm	*farm;
	char 	*str;

	farm = create_farm();
	while (get_next_line(0, &str))
	{
		if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
		{
			ft_putstr(GREEN);
			ft_putendl(str);
			ft_putstr(RESET);
			if (ft_strequ(str, "##start"))
			{
				free(str);
				if (get_next_line(0, &str))
				{
					ft_putstr(GREEN);
					ft_putendl(str);
					ft_putstr(RESET);
					farm->start = read_value(str, 0);
				}
			}
			if (ft_strequ(str, "##end"))
			{
				free(str);
				if (get_next_line(0, &str))
				{
					ft_putstr(GREEN);
					ft_putendl(str);
					ft_putstr(RESET);
					farm->end = read_value(str, 0);
				}
			}
		}
		else
		{
			ft_putstr(BLUE);
			ft_putendl(str);
			ft_putstr(RESET);
		}
		free(str);
	}
	
	printf("%sstart: %i\nend: %i\n%s", RED, farm->start, farm->end, RESET);

	return 0;
}