#include "../lemin.h"

void		spawn_ants(t_farm *farm)
{
	int i;

	i = 0;
	while (i < farm->ants)
	{
		ft_lstaddend(&farm->crew ,to_lst(new_ant(++i, farm->start)));
	}
	// printf("all ants are in\n");
}

void		ant_info(t_ant *ant)
{
	ft_putstr("L");
	ft_putnbr(ant->id);
	ft_putstr("-");
	ft_putstr(ant->location->name);
}

int			check_way(t_ant *ant, t_room *way, t_farm *farm)
{
	t_list *lst;
	t_room *room;

	// printf("check_way\n");
	lst = ant->location->connections;
	while (lst)
	{
		room = lst->content;

		// printf("room: %s (%i)   ant-location: %s (%i)\n",
		// 	room->name, room->weight, ant->location->name, ant->location->weight);
		// if (!room->lock)
		// 	printf("room is UNLOCKED\n");
		// else
		// 	printf("room is L O C K E D\n");
		// if (is_way_exist(room, way))
		// 	printf("WAY EXIST");
		// else
		// 	printf("WAY no EXIST");

		if (!room->lock && is_way_exist(room, way) &&
			room->weight > ant->location->weight)
		{
			ant->location->lock = 0;
			ant->location = room;
			if (ant->location->weight < 2147483647)
				ant->location->lock = 1;
			else
				farm->counter++;
			ant_info(ant);
			ft_putstr(" ");
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int			check_status(t_list *status, t_room *room)
{
	t_list *lst;

	lst = status;
	while (lst)
	{
		if (lst->content == room)
			return (0);
		lst = lst->next;
	}
	return (1);
}

void		move_ant(t_ant *ant, t_farm *farm, t_list **status)
{
	t_list *lst;
	t_room *way;

	// printf("move ANT\n");
	if (ant->location->weight == 2147483647)
		return ;
	lst = ant->location->ways;
	while (lst)
	{
		way = lst->content;
		if (!ant->location->weight && check_status(*status, way) &&
			check_way(ant, way, farm))
		{
			ft_lstadd(status, to_lst(way));
			return ;
		}
		if (ant->location->weight && check_way(ant, way, farm))
		{
			return ;
		}
		lst = lst->next;
	}
}

void		move_ants(t_farm *farm)
{
	t_list *lst;
	t_ant *curr_ant;
	t_list *status;

	status = NULL;
	// printf("move_ants\n");
	lst = farm->crew;
	while (lst)
	{
		curr_ant = lst->content;
		move_ant(curr_ant, farm, &status);
		lst = lst->next;
	}
	while (status)
	{
		lst = status->next;
		free(status);
		status = lst;
	}
}