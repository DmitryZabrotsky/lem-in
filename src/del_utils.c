/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 16:07:18 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 16:07:20 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lemin.h"

int					is_ant_here(t_room *room, t_farm *farm)
{
	t_list			*lst;
	t_ant			*ant;

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

void				del_way(t_room *room, t_room *way)
{
	t_list			*prev;
	t_list			*next;
	t_list			*lst;
	t_room			*r;

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
