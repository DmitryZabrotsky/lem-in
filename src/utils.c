#include "../lemin.h"

t_farm *create_farm()
{
	t_farm *res;

	if ((res = (t_farm *)malloc(sizeof(t_farm))))
	{
		res->start = -1;
		res->end = -1;
	}
	return (res);
}