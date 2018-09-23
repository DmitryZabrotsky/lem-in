/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 15:55:04 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 15:55:30 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lemin.h"

int					is_way_norm(t_room *room, t_room *way)
{
	t_list			*lst;
	t_room			*r;

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

void				free_lst(t_list *lst)
{
	if (!lst)
		return ;
	free_lst(lst->next);
	free(lst);
}

int					clear_ways(t_room *room, t_room *way)
{
	static	t_list	*checked = NULL;
	t_list			*lst;
	t_room			*r;

	lst = room->connections;
	ft_lstadd(&checked, to_lst(room));
	while (lst)
	{
		r = lst->content;
		if (r->weight == 2147483647)
		{
			free_lst(checked);
			checked = NULL;
			return (1);
		}
		if (r->weight >= room->weight && is_way_exist(r, way)
			&& check_status(checked, r))
			return (clear_ways(r, way));
		lst = lst->next;
	}
	del_way(room, way);
	free_lst(checked);
	checked = NULL;
	return (0);
}

void				del_broken_ways(t_farm *farm)
{
	t_list			*lst;
	t_list			*lst1;
	t_room			*room;

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
				lst1 = lst1->next;
			}
		}
		lst = lst->next;
	}
	lst = farm->rooms;
}

void				unlock_rooms(t_farm *farm)
{
	t_list			*lst;
	t_room			*room;

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
