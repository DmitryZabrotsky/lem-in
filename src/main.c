#include "../lemin.h"

void del_room(t_room *room)
{
	t_list *lst;
	t_list *lstnext;

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

void del_farm(t_farm *farm)
{
	t_list *lst;
	t_list *next;
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
		free(lst->content);
		free(lst);
		lst = next;
	}

	free(farm);
}

void error_manager(int code, t_farm *farm)
{
	if (code == 0)
	{
		ft_putendl(RED "ERROR" RESET);
		del_farm(farm);
		exit(1);
	}
}

int main(void)
{
	t_farm *farm;

	farm = new_farm();
	error_manager(stage_one(farm), farm);
	stage_three(stage_two(farm), farm);
	start_handleing(farm);
	ft_putendl(YELLOW "--     --" RESET);
	describe_farm(farm);

	spawn_ants(farm);
	while (farm->counter < farm->ants)
	{
		move_ants(farm);
		ft_putendl("");
	}

	del_farm(farm);

	while (42)
	{

	}
}