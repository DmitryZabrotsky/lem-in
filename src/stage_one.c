/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stage_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:37:01 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/11 16:37:02 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lemin.h"

int			is_int(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_ants(char *s, t_farm *farm)
{
	if (!is_int(s))
	{
		free(s);
		return (0);
	}
	farm->ants = ft_atoi(s);
	if (*s)
		ft_putendl(s);
	free(s);
	if (farm->ants <= 0 || farm->ants > 10000)
		return (0);
	return (1);
}

int			stage_one(t_farm *farm)
{
	char	*s;

	while (get_next_line(0, &s) > 0)
	{
		if (s[0] != '#')
			return (parse_ants(s, farm));
		if (*s)
			ft_putendl(s);
		free(s);
	}
	return (0);
}
