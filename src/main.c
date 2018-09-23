/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:35:10 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/11 16:35:20 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lemin.h"

void			del_room(t_room *room)
{
	t_list		*lst;
	t_list		*lstnext;

	if (!room)
		return ;
	free(room->name);
	lst = room->connections;
	while (lst)
	{
		lstnext = lst->next;
		free(lst);
		lst = lstnext;
	}
	lst = room->ways;
	while (lst)
	{
		lstnext = lst->next;
		free(lst);
		lst = lstnext;
	}
	free(room);
}

void			del_farm(t_farm *farm)
{
	t_list		*lst;
	t_list		*next;
	t_ant		*ant;

	lst = farm->rooms;
	while (lst)
	{
		next = lst->next;
		del_room(lst->content);
		free(lst);
		lst = next;
	}
	lst = farm->crew;
	while (lst)
	{
		next = lst->next;
		ant = lst->content;
		free_lst(ant->checked);
		free(lst->content);
		free(lst);
		lst = next;
	}
	free(farm);
}

void			error_manager(int code, t_farm *farm)
{
	if (code == 0)
	{
		ft_putendl(RED "ERROR" RESET);
		del_farm(farm);
		exit(1);
	}
}

static void		spawn_ants(t_farm *farm)
{
	int			i;

	i = 0;
	while (i < farm->ants)
	{
		ft_lstaddend(&farm->crew, to_lst(new_ant(++i, farm->start)));
	}
}

int				main(void)
{
	t_farm *farm;

	farm = new_farm();
	error_manager(stage_one(farm), farm);
	stage_three(stage_two(farm), farm);
	if (!farm->end || !farm->start)
		error_manager(0, farm);
	start_handleing(farm);
	spawn_ants(farm);
	check_start_end_connection(farm);
	while (farm->counter < farm->ants)
	{
		move_ants(farm);
		ft_putendl("");
	}
	del_farm(farm);
}
