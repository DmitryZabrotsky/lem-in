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
		if (way && !ant->way && check_status(*status, way))
		{
			ant->way = way;
			ft_lstadd(status, to_lst(way));
			return ;
		}
		lst = lst->next;
	}
	if (ant->way)
		check_way(ant, ant->way, farm);
}

void		move_ants(t_farm *farm)
{
	t_list	*lst;
	t_ant	*curr_ant;
	t_list	*status;

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
