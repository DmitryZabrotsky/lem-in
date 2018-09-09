#include "../lemin.h"

int				

static void		set_ways(t_room *room, t_room *name)
{
	t_room *buf;
	t_list *lst;

	lst = lst->connections;
	while (lst)
	{
		buf = lst->conntent;
		if ()
	}
}

static int		is_connected(t_room *start)
{
	t_room *buf;
	t_list *lst;

	lst = start->connections;
	while (lst)
	{
		buf = lst->conntent;
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
	farm->start->weight = 2147483647;
	farm->end->weight = 0;
	set_weights(farm->end);
	error_manager(is_connected(farm->start), farm);
	set_ways(farm->end);
}