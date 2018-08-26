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

	if ((res = (t_farm *)malloc(sizeof(t_room))))
	{
		res->name = NULL;
		res->x = -1;
		res->y = -1;
		res->connections = NULL;
	}
	return (res);
}