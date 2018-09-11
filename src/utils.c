/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:37:35 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/11 16:37:39 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lemin.h"

t_farm		*new_farm(void)
{
	t_farm	*res;

	if ((res = (t_farm *)malloc(sizeof(t_farm))))
	{
		res->start = NULL;
		res->end = NULL;
		res->ants = -1;
		res->rooms = NULL;
		res->crew = NULL;
		res->counter = 0;
	}
	return (res);
}

t_room		*new_room(void)
{
	t_room	*res;

	if ((res = (t_room *)malloc(sizeof(t_room))))
	{
		res->name = NULL;
		res->x = -1;
		res->y = -1;
		res->connections = NULL;
		res->weight = -1;
		res->ways = NULL;
		res->lock = 0;
	}
	return (res);
}

t_ant		*new_ant(int id, t_room *start)
{
	t_ant	*res;

	if ((res = (t_ant *)malloc(sizeof(t_ant))))
	{
		res->id = id;
		res->location = start;
	}
	return (res);
}

t_list		*to_lst(void *obj)
{
	t_list	*lst;

	lst = ft_lstnew(NULL, 0);
	lst->content = obj;
	return (lst);
}
