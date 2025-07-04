/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 01:40:38 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/04 12:54:06 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	light_config(const char **params, t_light **light)
{
	if (!params_config(params, 2)
		&& !params_config(params, 3))
		return (*light = NULL, false);
	*light = ft_calloc(1, sizeof(t_light));
	if (!*light)
		return (false);
	(*light)->type = LIGHT;
	if (**params == AMBIENT)
		(*light)->type = AMBIENT;
	if (!init_vec(params[((*light)->type == AMBIENT) + 1], &(*light)->pos))
		return (free(*light), *light = NULL, false);
	(*light)->ratio = ft_atof(params[((*light)->type == LIGHT) + 1]);
	if (params[3] && !init_color(params[3], &(*light)->color))
		return (free(*light), *light = NULL, false);
	else
		return (true);
}

bool	camera_config(const char **params, t_camera **camera)
{
	if (!params_config(params, 3))
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
