/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hodilka.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:34:57 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/11 16:35:01 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lemin.h"

void		ant_info(t_ant *ant)
{
	ft_putstr("L");
	ft_putnbr(ant->id);
	ft_putstr("-");
	ft_putstr(ant->location->name);
}

int			check_way(t_ant *ant, t_room *way, t_farm *farm)
{
	t_list	*lst;
	t_room	*room;

	lst = ant->location->connections;
	while (lst)
	{
		room = lst->content;
		// if (ant->id == 1)
		// printf("location %s room %s !\n", ant->location->name, room->name);
		
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
	// lst = ant->location->connections;
	// while (lst)
	// {
	// 	room = lst->content;
	// 	// if (ant->id == 1)
	// 	// printf("location %s room %s !\n", ant->location->name, room->name);

	// 	if (!room->lock && is_way_exist(room, way) &&
	// 		room->weight >= ant->location->weight)
	// 	{
	// 		ant->location->lock = 0;
	// 		ant->location = room;
	// 		if (ant->location->weight < 2147483647)
	// 			ant->location->lock = 1;
	// 		else
	// 			farm->counter++;
	// 		ant_info(ant);
	// 		ft_putstr(" ");
	// 		return (1);
	// 	}
	// 	lst = lst->next;
	// }
	return (0);
}

int			check_status(t_list *status, t_room *room)
{
	t_list	*lst;

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
	t_list	*lst;
	t_room	*way;

	if (ant->location->weight == 2147483647)
		return ;
	lst = ant->location->ways;
	while (lst)
	{
		way = lst->content;
		if (!ant->location->weight && check_status(*status, way) &&
			check_way(ant, way, farm))
		{
			//printf("L%i steps from start\n", ant->id);
			ft_lstadd(status, to_lst(way));
			return ;
		}
		if (ant->location->weight && check_way(ant, way, farm))
		{
			//printf("L%i steps\n", ant->id);
			return ;
		}
		lst = lst->next;
	}
}

void		move_ants(t_farm *farm)
{
	t_list	*lst;
	t_ant	*curr_ant;
	t_list	*status;

	//printf("move_ants\n");
	status = NULL;
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
