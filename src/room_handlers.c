#include "../lemin.h"

void			delete_other_ways(t_room *room)
{
	t_list *ways;
	t_room *buf;

	t_list *prev;
	t_list *next;

	ways = room->ways;
	prev = NULL;
	while (ways)
	{
		buf = ways->content;
		next = ways->next;
		printf("buf = %s\n", buf->name);
		if (buf->name != room->name)
		{
			if (prev)
				prev->next = next;
			else if (!prev)
				room->ways = next;
			free(ways);
			printf("need to del %s in %s\n", buf->name,  room->name);
		}
		else
			prev = ways;
		ways = next;
	}
}

void			check_near_rooms(t_room *end)
{
	t_room *room;
	t_list *connections;
	t_list *ways;

	connections = end->connections;
	while (connections)
	{
		room = connections->content;
		ways = room->ways;
		while (ways)
		{
			if (ways->content != room)
				delete_other_ways(room);
			ways = ways->next;
		}
		connections = connections->next;
	}
}

// static void		optimize_ways(t_room *room, t_room *name)
// {
// 	t_room *buf;
// 	t_list *lst;

// 	lst = room->connections;
// 	if (!room->weight)
// 		return ;
// 	while (lst)
// 	{
// 		buf = lst->content;
// 		if (buf->weight == 2147483647)
// 			ft_lstaddend(&buf->ways, to_lst(name));
// 		if (!is_way_exist(buf, name) && (room->weight >= buf->weight
// 			&& buf->weight != 2147483647))
// 				set_ways(buf, name);
// 		lst = lst->next;
// 	}
// }

int				is_way_exist(t_room *room, t_room *name)
{
	t_list	*lst;

	lst = room->ways;
	while (lst)
	{
		if (lst->content == name)
			return (1);
		lst = lst->next;
	}
	return (0);
}

static void		set_ways(t_room *room, t_room *name)
{
	t_room *buf;
	t_list *lst;

	lst = room->connections;
	printf("room: %s  name: %s\n", room->name, name->name);
	ft_lstaddend(&room->ways, to_lst(name));
	if (!room->weight)
	{
		printf("e n d\n");
		return ;
	}
	while (lst)
	{
		buf = lst->content;
		if (buf->weight == 2147483647)
			ft_lstaddend(&buf->ways, to_lst(name));
		if (!is_way_exist(buf, name) && (room->weight >= buf->weight
			&& buf->weight != 2147483647))
				set_ways(buf, name);
		lst = lst->next;
	}
}

static int		is_connected(t_room *start)
{
	t_room *buf;
	t_list *lst;

	lst = start->connections;
	while (lst)
	{
		buf = lst->content;
		if (buf->weight != -1)
			return (1);
		lst = lst->next;
	}
	return (0);
}

static void		set_weights(t_room *room)
{
	t_room *buf;
	t_list *lst;
	
	lst = room->connections;
	while (lst)
	{
		buf = lst->content;
		if (buf->weight != 2147483647 && (buf->weight == -1 ||
			buf->weight > room->weight + 1))
		{
			buf->weight = room->weight + 1;
			set_weights(buf);
		}
		lst = lst->next;
	}
}

void		start_handleing(t_farm *farm)
{
	t_room *buf;
	t_list *lst;

	farm->start->weight = 0;
	farm->end->weight = 2147483647;
	set_weights(farm->start);
	error_manager(is_connected(farm->end), farm);
	
	lst = farm->end->connections;
	while (lst)
	{
		buf = lst->content;
		set_ways(buf, buf);
		lst = lst->next;
	}
	check_near_rooms(farm->end);
}