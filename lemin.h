/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 17:02:44 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/11 17:02:48 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "./libft/incl/libft.h"

typedef	struct	s_room {
	char		*name;
	int			x;
	int			y;
	t_list		*connections;
	int			weight;
	t_list		*ways;
	int			lock;
}				t_room;

typedef struct	s_farm {
	t_room		*start;
	t_room		*end;
	int			ants;
	t_list		*crew;
	t_list		*rooms;
	int			counter;
}				t_farm;

typedef struct	s_ant {
	int			id;
	t_room		*way;
	t_room		*location;
	t_list		*checked;
}				t_ant;

void			error_manager(int code, t_farm *farm);

/*
 ** utils.c
*/
t_farm			*new_farm();
t_room			*new_room();
t_list			*to_lst(void *obj);
void			describe_farm(t_farm *farm);
t_ant			*new_ant(int id, t_room *start);

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
int				is_rooms_connected(t_room *room1, t_room *room2);


/*
 ** stage_three.c
*/
void			stage_three(char *s, t_farm *farm);
t_room			*get_room(char *s, t_farm *farm);

/*
 ** room_handler.c
*/
void			start_handleing(t_farm *farm);
int				is_way_exist(t_room *room, t_room *name);

void			move_ants(t_farm *farm);

void			check_near_rooms(t_room *end);
void			sort_ways(t_room *room);
void			sort_all_ways(t_room *room);
void			check_rooms(t_room *room, t_room *way);

int				count_chars(char *s, char c);
void			del_farm(t_farm *farm);
void			check_start_end_connection(t_farm *farm);
void			ant_info(t_ant *ant);
void			sort_connections(t_room *room);
void			sort_all_connections(t_room *room);
void			del_broken_ways(t_farm* farm);
int				check_status(t_list *status, t_room *room);



#endif
