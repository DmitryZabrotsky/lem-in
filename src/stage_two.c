/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stage_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:37:07 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/11 16:37:08 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lemin.h"

int			check_num_of_parts(char **arr, int etalon)
{
	int		i;

	i = 0;
	while (arr[i])
		i++;
	if (i != etalon)
		return (0);
	return (1);
}

static int	check_room_name(char *name)
{
	int		i;

	i = 0;
	if (name[0] == 'L')
		return (0);
	while (name[i])
	{
		if (!ft_isascii(name[i]) || name[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

static int	is_room(char **arr, t_farm *farm)
{
	if (!check_num_of_parts(arr, 3))
		return (0);
	if (!check_room_name(arr[0]))
		return (0);
	if (!is_int(arr[1]) || !is_int(arr[2]))
		return (0);
	if (get_room(arr[0], farm))
		return (0);
	return (1);
}

static int	parse_rooms(t_farm *farm, char *s, int status)
{
	t_room	*room;
	char	**arr;

	arr = ft_strsplit(s, ' ');
	if (count_chars(s, ' ') != 2 || !is_room(arr, farm))
	{
		ft_arrfree(&arr);
		return (0);
	}
	room = new_room();
	room->name = ft_strdup(arr[0]);
	room->x = ft_atoi(arr[1]);
	room->y = ft_atoi(arr[2]);
	ft_arrfree(&arr);
	ft_lstaddend(&farm->rooms, to_lst(room));
	if (status == 1 && !farm->start)
		farm->start = room;
	else if (status == 1)
		return (0);
	if (status == 2 && !farm->end)
		farm->end = room;
	else if (status == 2)
		return (0);
	return (1);
}

char		*stage_two(t_farm *farm)
{
	char	*s;
	int		status;

	while (get_next_line(0, &s) > 0)
	{
		if (ft_strequ("##start", s))
			status = 1;
		else if (ft_strequ("##end", s))
			status = 2;
		else if (s[0] != '#')
		{
			if (!parse_rooms(farm, s, status))
				return (s);
			status = 0;
		}
		ft_putendl(s);
		free(s);
	}
	return (NULL);
}
