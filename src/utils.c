#include "../lemin.h"

t_farm *new_farm()
{
	t_farm *res;

	if ((res = (t_farm *)malloc(sizeof(t_farm))))
	{
		res->start = NULL;
		res->end = NULL;
		res->ants = -1;
		res->rooms = NULL;
	}
	return (res);
}

t_room *new_room()
{
	t_room *res;

	if ((res = (t_room *)malloc(sizeof(t_room))))
	{
		res->name = NULL;
		res->x = -1;
		res->y = -1;
		res->connections = NULL;
	}
	return (res);
}

void describe_room(t_room *room)
{
	t_list *lst;
	t_room *buf;

	printf("name: %s\nx: %i y: %i\n", room->name, room->x, room->y);

	lst = room->connections;
	while (lst)
	{
		buf = lst->content;
		printf("%s ", buf->name);
		lst = lst->next;
	}
	printf("\n");
}

void describe_farm(t_farm * farm)
{
	t_list *lst;
	t_room *buf;

	if (farm->start)
		printf("start: %s\n", farm->start->name);
	else
		printf("no start!\n");
	if (farm->end)
		printf("end: %s\n", farm->end->name);
	else
		printf("no end!\n");
	printf("ants: %i\n", farm->ants);

	lst = farm->rooms;
	while (lst)
	{
		buf = lst->content;
		printf("-- room --\n");
		describe_room(buf);
		lst = lst->next;
	}
}