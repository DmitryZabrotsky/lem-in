#ifndef LEMIN_H
# define LEMIN_H

# include "./libft/incl/libft.h"
# include <stdio.h>

typedef	struct s_room {
	char		*name;
	int			x;
	int			y;
	t_list		*connections;
}				t_room;

typedef struct	s_farm {
	t_room		*start;
	t_room		*end;
	int			ants;
	t_list		*rooms;
}				t_farm;

t_farm			*new_farm();
t_room			*new_room();
void			describe_farm(t_farm *farm);

#endif