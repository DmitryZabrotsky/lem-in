#ifndef LEMIN_H
# define LEMIN_H

# include "./libft/incl/libft.h"
# include <stdio.h>

typedef struct	s_farm {
	int			start;
	int			end;
}				t_farm;

t_farm			*create_farm();

#endif