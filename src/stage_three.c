#include "../lemin.h"

t_room		*get_room(char *s, t_farm *farm)
{
	t_list *lst;
	t_room *buf;

	lst = farm->rooms;
	while (lst)
	{
		buf = lst->content;
		if (ft_strequ(buf->name, s))
			return (buf);
		lst = lst->next;
	}
	return (NULL);
}

static int			parse_connection(char *s, t_farm *farm)
{
	char **arr;
	t_room *room1;
	t_room *room2;

	arr = ft_strsplit(s, '-');
	if (!check_num_of_parts(arr, 2))
	{
		ft_arrfree(&arr);
		return (0);
	}
	room1 = get_room(arr[0], farm);
	room2 = get_room(arr[1], farm);
	ft_arrfree(&arr);
	if (!room1 || !room2)
	{
		printf("wrong room in connections\n");
		return (0);
	}
	ft_lstaddend(&room1->connections, to_lst(room2));
	ft_lstaddend(&room2->connections, to_lst(room1));
	return (1);
}

void		stage_three(char *s, t_farm *farm)
{
	if (!s)
		return ;
	while (42)
	{
		if (s[0] != '#' && !parse_connection(s, farm))
		{
			free(s);
			return ;
		}
		ft_putendl(s);
		free(s);
		if (get_next_line(0, &s) < 1)
			return ;
	}
}