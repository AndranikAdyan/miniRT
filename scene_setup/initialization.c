/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 01:31:03 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/03 01:26:17 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	light_config(t_light **light, char **params)
{
	int	pos_index;

	if (!params_config((const char **)params, 2)
		&& !params_config((const char **)params, 3))
		return (*light = NULL, false);
	pos_index = !ft_strncmp(params[0], "A", 2) + 1;
	*light = ft_calloc(1, sizeof(t_light));
	if (!*light)
		return (false);
	if (!init_vec(params[pos_index], &(*light)->pos))
		return (free(*light), *light = NULL, false);
	(*light)->ratio = ft_atof(params[pos_index == 1]);
	if (params[2] && !init_color(params[2], &(*light)->color))
		return (free(*light), *light = NULL, false);
	if (pos_index != 1)
		(*light)->type = AMBIENT;
	return (true);
}

bool	camera_config(t_camera **camera, char **params)
{
	if (!params_config((const char **)params, 3))
		return (*camera = NULL, false);
	*camera = ft_calloc(1, sizeof(t_camera));
	if (!*camera)
		return (false);
	if (!init_vec(params[1], &(*camera)->pos)
		|| !init_vec(params[2], &(*camera)->dir))
		return (free(*camera), *camera = NULL, false);
	(*camera)->fov = ft_atoi(params[3]);
	return (true);
}
/*
bool	object_config(t_object **object, char **params)
{
	if ((!ft_strncmp(*params, "sp", 3) && !params_config(params, 3))
		|| (!ft_strncmp(*params, *params, "pl", 3) && !params_config(params, 3))
		|| (!ft_strncmp(*params, *params, "cy", 3) && !params_config(params, 5)))
		return (*object = NULL, false);
	*object = ft_calloc(1, sizeof(t_object));
	if (!*object)
		return (false);
	(*sphere)->diameter = ft_atof(params[2]);
	if (!init_vec(params[1], (*sphere)->pos)
		|| !init_color(params[2], (*sphere)->color))
		return (free(*sphere), *sphere = NULL, false);
	return (true);
}
*/
