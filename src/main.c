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

void print_list(t_list *lst)
{
	t_list *tmp;

	tmp = lst;
	while (tmp)
	{
		printf("%s%s%10zu%s\n\n", BLUE, tmp->content, tmp->content_size, RESET);
		tmp = tmp->next;
	}
}

int			main(void)
{
	t_list	*file;
	t_farm	*farm;
	char 	*str;

	file = NULL;
	farm = create_farm();
	while (get_next_line(0, &str))
	{
		ft_lstaddend(&file, ft_lstnew(str, ft_strlen(str)));
		if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
		{
			if (ft_strequ(str, "##start"))
			{
				free(str);
				if (get_next_line(0, &str))
				{
					farm->start = read_value(str, 0);
				}
			}
			if (ft_strequ(str, "##end"))
			{
				free(str);
				if (get_next_line(0, &str))
				{
					farm->end = read_value(str, 0);
				}
			}
		}
		free(str);
	}
	
	print_list(file);
	printf("%sstart: %i\nend: %i\n%s", GREEN, farm->start, farm->end, RESET);

	return 0;
}