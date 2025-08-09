/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 01:59:50 by saslanya          #+#    #+#             */
/*   Updated: 2025/08/09 17:56:55 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	free_split(char ***s)
{
	size_t	i;

	i = 0;
	if (!*s)
		return ;
	while ((*s)[i])
	{
		free((*s)[i]);
		++i;
	}
	free(*s);
	*s = NULL;
	return ;
}

bool	between_range(double value, double min, double max)
{
	return (value >= min && value <= max);
}

bool	init_vec(const char *s, t_vec *pos, double min, double max)
{
	char	**param;

	param = ft_split(s, ',');
	if (!param || params_count((const char **)param) != VEC_ARG_SIZE)
		return (free_split(&param), false);
	pos->x = ft_atof(param[0]);
	pos->y = ft_atof(param[1]);
	pos->z = ft_atof(param[2]);
	free_split(&param);
	if (min != max)
		return (between_range(pos->x, min, max)
			&& between_range(pos->y, min, max)
			&& between_range(pos->z, min, max));
	return (true);
}

bool	init_color(const char *s, t_rgb *color)
{
	char	**param;

	param = ft_split(s, ',');
	if (!param || params_count((const char **)param) != 3)
		return (free_split(&param), false);
	color->red = ft_atof(param[0]);
	color->green = ft_atof(param[1]);
	color->blue = ft_atof(param[2]);
	free_split(&param);
	if (!between_range(color->red, 0.0, 255.0)
		|| !between_range(color->green, 0.0, 255.0)
		|| !between_range(color->blue, 0.0, 255.0))
		return (false);
	color->red = eotf(color->red);
	color->green = eotf(color->green);
	color->blue = eotf(color->blue);
	return (true);
}

bool	camera_config(const char **params, t_camera **camera)
{
	if (!params_config(params, 3))
		return (*camera = NULL, false);
	*camera = ft_calloc(1, sizeof(t_camera));
	if (!*camera)
		return (false);
	if (!init_vec(params[1], &(*camera)->pos, 0.0, 0.0)
		|| !init_vec(params[2], &(*camera)->dir, -1.0, 1.0))
		return (free(*camera), *camera = NULL, false);
	(*camera)->fov = ft_atoi(params[3]);
	if (!between_range((*camera)->fov, 0.0, 180.0))
		return (free(*camera), *camera = NULL, false);
	return (true);
}
