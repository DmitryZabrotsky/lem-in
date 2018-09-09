#include "../lemin.h"

void		spawn_ants(t_farm *farm)
{
	int i;

	i = 0;
	while (i < farm->ants)
	{
		ft_lstaddend(&farm->crew ,to_lst(new_ant(++i, farm->start)));
	}
	printf("all ants are in\n");
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

	printf("check_way\n");
	lst = ant->location->connections;
	while (lst)
	{
		room = lst->content;
		if (!room->lock && is_way_exist(room, way) &&
			room->weight < ant->location->weight)
		{
			ant->location->lock = 0;
			ant->location = room;
			if (ant->location->weight > 0)
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

void		move_ant(t_ant *ant, t_farm *farm)
{
	t_list *lst;
	t_room *way;

	printf("move ANT\n");
	if (ant->location->weight == 0)
		return ;
	lst = ant->location->ways;
	while (lst)
	{
		way = lst->content;
		if (check_way(ant, way, farm))
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

	printf("move_ants\n");
	lst = farm->crew;
	while (lst)
	{
		curr_ant = lst->content;
		move_ant(curr_ant, farm);
		lst = lst->next;
	}
}