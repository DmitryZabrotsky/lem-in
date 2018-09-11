/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 17:00:35 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/11 17:00:37 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lemin.h"

void		sort_ways(t_room *room)
{
	t_list *lst;
	t_list *next;
	t_room *r1;
	t_room *r2;

	lst = room->ways;
	if (!lst)
		return ;
	next = lst->next;
	while (next)
	{
		r1 = lst->content;
		r2 = next->content;
		if (r1->weight > r2->weight)
		{
			lst->content = r2;
			next->content = r1;
			sort_ways(room);
		}
		else
		{
			lst = next;
			next = lst->next;
		}
	}
}

int			count_chars(char *s, char c)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

static int	check_check_start_end_connection(t_farm *farm)
{
	t_list	*lst;
	t_room	*room;

	lst = farm->start->connections;
	while (lst)
	{
		room = lst->content;
		if (room == farm->end)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void		check_start_end_connection(t_farm *farm)
{
	t_list	*lst;
	t_ant	*ant;

	if (!check_check_start_end_connection(farm))
		return ;
	lst = farm->crew;
	while (lst)
	{
		ant = lst->content;
		ant->location = farm->end;
		ant_info(ant);
		ft_putstr(" ");
		lst = lst->next;
	}
	ft_putendl(MAGENTA "\nWARNING! start connected with end!" RESET);
	del_farm(farm);
	exit(0);
}
