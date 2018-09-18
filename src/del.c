#include "../lemin.h"

int			is_way_norm(t_room *room, t_room *way)
{
	t_list *lst;
	t_room *r;

	printf("is_way_norm\n");
	lst = room->connections;
	while (lst)
	{
		r = lst->content;
		if (!r->weight)
			return (1);
		if (r->weight < room->weight && is_way_exist(r, way)
			&& is_way_norm(r, way))
			return (1);
		lst = lst->next;
	}
	return (0);
}

void			del_way(t_room *room, t_room *way)
{
	t_list *prev;
	t_list *next;
	t_list *lst;
	t_room *r;

	printf("del_way\n");
	lst = room->ways;
	prev = NULL;
	while (lst)
	{
		next = lst->next;
		r = lst->content;
		if (r == way)
		{
			if (!prev)
				room->ways = next;
			else
				prev->next = next;
			free(lst);
		}
		else
			prev = lst;
		lst = next;
	}
}

void			free_lst(t_list *lst)
{
	printf("free_lst\n");
	if (!lst)
	{
		//printf("lst non exist\n");
		return;
	}
	//printf("lst exist\n");
	free_lst(lst->next);
	free(lst);
	//printf("wtf\n");
}


int				clear_ways(t_room *room, t_room *way)
{
	static	t_list	*checked = NULL;
	t_list 			*lst;
	t_room			*r;

	printf("clear_ways location  %s way %s\n", room->name, way->name);
	lst = room->connections;
	ft_lstadd(&checked, to_lst(room));
	while (lst)
	{
		r = lst->content;
		if (r->weight == 2147483647)
		{
			free_lst(checked);
			checked = NULL;
			printf("this is end!\n");
			return (1);
		}
		if (r->weight >= room->weight && is_way_exist(r, way)
			&& check_status(checked, r))
		{
			return (clear_ways(r, way));
		}
		lst = lst->next;
	}
	del_way(room, way);
	free_lst(checked);
	printf("oh no(((\n");
	checked = NULL;
	return (0);
}

void			del_broken_ways(t_farm* farm)
{
	t_list *lst;
	t_list *lst1;
	t_room *room;

	printf("del_broken_ways\n");
	lst = farm->start->ways;
	while (lst)
	{
		room = lst->content;
		if (!is_way_norm(room, room))
			lst->content = NULL;
		else
		{
			lst1 = farm->start->connections;
			while (lst1)
			{
				clear_ways(lst1->content, room);
				//sleep(2);
				lst1 = lst1->next;
			}
		}
		lst = lst->next;
	}
	lst = farm->rooms;
}

static int		is_ant_here(t_room *room, t_farm *farm)
{
	t_list *lst;
	t_ant *ant;

	lst = farm->crew;
	while (lst)
	{
		ant = lst->content;
		if (ant)
		{
			if (room == ant->location)
				return (1);
			lst = lst->next;
		}
	}
	return (0);
}

void			unlock_rooms(t_farm *farm)
{
	t_list	*lst;
	t_room 	*room;

	lst = farm->rooms;
	while (lst)
	{
		room = lst->content;
		if (room)
		{
			if (!is_ant_here(room, farm))
				room->lock = 0;
			lst = lst->next;
		}
	}
}
