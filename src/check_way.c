/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_way.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 16:21:29 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 16:21:31 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lemin.h"

static int	check_way_3(t_ant *ant, t_room *way, t_farm *farm)
{
	t_list	*lst;
	t_room	*room;

	lst = ant->location->connections;
	while (lst)
	{
		room = lst->content;
		if (!room->lock && room->weight && is_way_exist(room, way))
		{
			ant->location = room;
			if (ant->location->weight < 2147483647)
				ant->location->lock = 1;
			else
				farm->counter++;
			ft_lstadd(&ant->checked, to_lst(ant->location));
			ant_info(ant);
			ft_putstr(" ");
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

static int	check_way_2(t_ant *ant, t_room *way, t_farm *farm)
{
	t_list	*lst;
	t_room	*room;

	ant->checked = NULL;
	lst = ant->location->connections;
	while (lst)
	{
		room = lst->content;
		if (!room->lock && is_way_exist(room, way) &&
			room->weight >= ant->location->weight)
		{
			ant->location = room;
			if (ant->location->weight < 2147483647)
				ant->location->lock = 1;
			else
				farm->counter++;
			ft_lstadd(&ant->checked, to_lst(ant->location));
			ant_info(ant);
			ft_putstr(" ");
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

static int	check_way_1(t_ant *ant, t_room *way, t_farm *farm)
{
	t_list	*lst;
	t_room	*room;

	lst = ant->location->connections;
	while (lst)
	{
		room = lst->content;
		if (!room->lock && is_way_exist(room, way) &&
			room->weight >= ant->location->weight &&
			check_status(ant->checked, room))
		{
			ant->location->lock = 0;
			ant->location = room;
			if (ant->location->weight < 2147483647)
				ant->location->lock = 1;
			else
				farm->counter++;
			ft_lstadd(&ant->checked, to_lst(ant->location));
			ant_info(ant);
			ft_putstr(" ");
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int			check_way(t_ant *ant, t_room *way, t_farm *farm)
{
	if (check_way_1(ant, way, farm))
		return (1);
	if (check_way_2(ant, way, farm))
		return (1);
	if (check_way_3(ant, way, farm))
		return (1);
	unlock_rooms(farm);
	return (0);
}
