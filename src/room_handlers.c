/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:36:49 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/11 16:36:52 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lemin.h"

int				is_way_exist(t_room *room, t_room *name)
{
	t_list		*lst;

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
	t_room		*buf;
	t_list		*lst;

	lst = room->connections;
	ft_lstaddend(&room->ways, to_lst(name));
	if (!room->weight)
		return ;
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
	t_room		*buf;
	t_list		*lst;

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
	t_room		*buf;
	t_list		*lst;

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

void			start_handleing(t_farm *farm)
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
	sort_all_ways(farm->start);
	sort_all_connections(farm->start);
	lst = farm->end->connections;
	while (lst)
	{
		buf = lst->content;
		check_rooms(buf, buf);
		lst = lst->next;
	}
	del_broken_ways(farm);
}
