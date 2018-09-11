#include "../lemin.h"

static void			check_room(t_room *room, t_room *way)
{
	t_list *lst;
	t_list *next;

	lst = room->ways;
	while (lst)
	{
		next = lst->next;
		free(lst);
		lst = next;
	}
	room->ways = to_lst(way);
}

void			check_near_rooms(t_room *end)
{
	t_list *lst;
	t_room *room;

	lst = end->connections;
	while (lst)
	{
		room = lst->content;
		if (room->weight > -1)
			check_room(lst->content, lst->content);
		lst = lst->next;
	}
}

void			sort_ways(t_room *room)
{
	t_list *lst;
	t_list *next;
	t_room *r1;
	t_room *r2;

	lst = room->ways;
	if (!lst)
		return ;
	next = lst->next;
	while (next)
	{
		r1 = lst->content;
		r2 = next->content;
		if (r1->weight > r2->weight)
		{
			lst->content = r2;
			next->content = r1;
			sort_ways(room);
		}
		else
		{
			lst = next;
			next = lst->next;
		}
	}
}

void			sort_all_ways(t_room *room)
{
	t_list *lst;
	t_room *buf;

	sort_ways(room);
	lst = room->connections;
	while (lst)
	{
		buf = lst->content;
		if (buf->weight > room->weight)
			sort_all_ways(buf);
		lst = lst->next;
	}
}

int				count_rooms_for_way(t_room *room, t_room *way)
{
	t_list *lst;
	t_room *buf;
	int		res;

	res = 0;
	lst = room->connections;
	while (lst)
	{
		buf = lst->content;
		if (buf->weight < room->weight && is_way_exist(buf, way))
			res++;
		lst = lst->next;
	}
	return (res);
}

void			check_rooms(t_room *room, t_room *way)
{
	int			ways_num;
	t_list		*lst;
	t_room		*buf;

	ways_num = count_rooms_for_way(room, way);
	printf("room: %s way: %s ways_num: %i\n", room->name, way->name, ways_num);
	lst = room->connections;
	while (lst)
	{
		buf = lst->content;
		if (buf->weight != 0 &&
			buf->weight < room->weight && is_way_exist(buf, way))
		{
			if (ways_num == 1)
				check_room(buf, way);
			check_rooms(buf, way);
		}
		lst = lst->next;
	}
}
