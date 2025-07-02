/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 01:31:03 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/03 00:00:12 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	light_config(t_light **light, char **params)
{
	int	pos_index;

	if (!params_config(params, 2) && !params_config(params, 3))
		return (*light = NULL, false);
	pos_index = !ft_strncmp(params[0], "A") + 1;
	*light = ft_calloc(1, sizeof(t_light));
	if (!*light)
		return (false);
	if (!init_vec(params[pos_index], (*light)->pos))
		return (free(*light), *light = NULL, false);
	(*light)->ratio = params[pos_index == 1];
	if (params[2] && !init_color(params[2], (*light)->color))
		return (free(*light), *light = NULL, false);
	return (true);
}

bool	camera_config(t_camera **camera, char **params)
{
	if (!params_config(params, 3))
		return (*camera = NULL, false);
	*camera = ft_calloc(1, sizeof(t_camera));
	if (!*camera)
		return (false);
	if (!init_vec(params[1], *camera->pos)
		|| !init_vec(params[2], (*camera)->dir))
		return (free(*camera), *camera = NULL, false);
	(*camera)->fov = ft_atoi(params[3]);
	return (true);
}

bool	sphere_config(t_sphere **sphere, char **params)
{
	if (!params_config(params, 3))
		return (*sphere = NULL, false);
	*sphere = ft_calloc(1, sizeof(t_sphere));
	if (!*sphere)
		return (false);
	(*sphere)->diameter = ft_atof(params[2]);
	if (!init_vec(params[1], (*sphere)->pos)
		|| !init_color(params[2], (*sphere)->color))
		return (free(*sphere), *sphere = NULL, false);
	return (true);
}
