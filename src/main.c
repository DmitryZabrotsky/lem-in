#include "../lemin.h"

void print_list(t_list *lst)
{
	t_list *tmp;

	tmp = lst;
	while (tmp)
	{
		//printf("%s%s%10zu%s\n", BLUE, tmp->content, tmp->content_size, RESET);
		ft_putendl((char *)tmp->content);
		tmp = tmp->next;
	}
}

int			read_value(char *str, int i)
{
	char **arr;
	int res;

	arr = ft_strsplit(str, ' ');
	res = ft_atoi(arr[i]);
	if (i = 0)
		return (arr[0]);
	ft_arrfree(&arr);
	return (res);
}

t_room *create_room(char *name, int x, int y)
{
	t_room	*res;

	if ((res = new_room()))
	{
		res->name = ft_strdup(name);
		res->x = x;
		res->y = y;
	}
	return (res);
}

int parse_ants(char ants, t_farm *farm)
{
	int i;

	i = 0;
	while (ants[i])
	{
		if (!ft_isdigit(ants[i]))
			return (0);
	}
	farm->ants = ft_atoi(ants);
	return (1);
}

t_list *to_lst(void *obj)
{
	t_list *lst;

	lst = ft_lstnew(NULL, 0);
	lst->content = obj;
	return (lst);
}

int check_num_of_parts(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	if (i > 2)
		return (0);
	return (1);
}

int check_room_name(char *name)
{
	int i;

	i = 0;
	while (name[i])
	{
		if(!ft_isalpha(name[i]))
			return (0);
	}
	return (1);
}

int check_coord(char *coord)
{
	int i;

	i = 0;
	while (ants[i])
	{
		if (!ft_isdigit(ants[i]))
			return (0);
	}
	return (1);
}

int is_room(char *str)
{
	char **arr;

	arr = ft_strsplit(str, ' ');
	if (!check_num_of_parts(arr))
		return (0);
	if (!check_room_name(arr[0]))
		return (0);
	if (!check_coord(arr[1]) || !check_coord(arr[2]))
		return (0);
	ft_arrfree(&arr);
	return (1);
}

int parse_room(char *str, t_farm *farm)
{
	t_room *room;
	char *name;
	int coord_x;
	int coord_y;

	if (!is_room(str))
		return (0);
	name = ft_strdup(read_value(str, 0));
	coord_x = ft_atoi(read_value(str, 1));
	coord_y = ft_atoi(read_value(str, 2));
	room = create_room(name, coord_x, coord_y);
	ft_lstaddend(farm->rooms, to_lst(room));
	return (1);
}

int parse_connection(char *str, t_farm *farm)
{
	return (1);
}

int parse_start_end(char **str, t_farm *farm)
{
	t_room *room;

	room = create_room();
	if (ft_strequ(*str, "##start"))
	{
		free(*str);
		if (get_next_line(0, &str))
		{
			farm->start = pointer on room;
		}
	}
	if (ft_strequ(str, "##end"))
	{
		free(str);
		if (get_next_line(0, &str))
		{
			farm->end = pointer on room;
		}
	}
	return (1);
}

int			main(void)
{
	t_list	*file;
	t_farm	*farm;
	char 	*str;

	file = NULL;
	farm = new_farm();
	while (get_next_line(0, &str))
	{
		ft_lstaddend(&file, ft_lstnew(str, ft_strlen(str) + 1));
		if (str[0] != '#')
		{
			prse_ants(str, farm);
			parse_room(str, farm);
			parse_connections(str, farm);
			if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
				parse_start_end(&str, farm);

		}
		printf("%s%s%s\n", YELLOW, str, RESET);
		free(str);
	}
	
	print_list(file);
	ft_lstfree(&file);
	printf("%sstart: %i\nend: %i\n%s", GREEN, farm->start, farm->end, RESET);

	// while (1)
	// {
		
	// }
	return 0;
}