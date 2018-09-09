#ifndef LEMIN_H
# define LEMIN_H

# include "./libft/incl/libft.h"
# include <stdio.h>

typedef	struct s_room {
	char		*name;
	int			x;
	int			y;
	t_list		*connections;
	int			weight;
	t_list		*way;
}				t_room;

typedef struct	s_farm {
	t_room		*start;
	t_room		*end;
	int			ants;
	t_list		*rooms;
}				t_farm;

/*
 ** utils.c
*/
t_farm			*new_farm();
t_room			*new_room();
t_list			*to_lst(void *obj);
void			describe_farm(t_farm *farm);

/*
 ** stage_one.c
*/
int				is_int(char *s);
int				stage_one(t_farm *farm);

/*
 ** stage_two.c
*/
char			*stage_two(t_farm *farm);
int				check_num_of_parts(char **arr, int etalon);

/*
 ** stage_three.c
*/
void			stage_three(char *s, t_farm *farm);
t_room			*get_room(char *s, t_farm *farm);

/*
 ** room_handler.c
*/
void			start_handleing(t_farm *farm);
#endif