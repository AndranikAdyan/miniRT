/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 01:40:38 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/23 00:07:22 by aadyan           ###   ########.fr       */
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
	if (!init_color(params[((*light)->type == LIGHT) + 2],
			&(*light)->color))
		return (free(*light), *light = NULL, false);
	(*light)->ratio = ft_atof(params[((*light)->type == LIGHT) + 1]);
	if ((*light)->type == LIGHT
		&& !init_vec(params[1], &(*light)->pos, 0.0, 0.0))
		return (free(*light), *light = NULL, false);
	if (!between_range((*light)->ratio, 0.0, 1.0))
		return (free(*light), *light = NULL, false);
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

static bool	sphere_config(const char **params, t_object **obj)
{
	*obj = ft_calloc(1, sizeof(t_object));
	if (!*obj)
		return (false);
	if (!init_vec(params[1], &((*obj)->variant.sphere.pos), 0.0, 0.0)
		|| !init_color(params[3], &((*obj)->variant.sphere.color)))
		return (free(*obj), *obj = NULL, false);
	(*obj)->variant.sphere.radius = ft_atof(params[2]) / 2.0;
	if ((*obj)->variant.sphere.radius <= 0.0)
		return (free(*obj), *obj = NULL, false);
	(*obj)->type = SPHERE;
	return (true);
}

static bool	cylinder_config(const char **params, t_object **obj)
{
	*obj = ft_calloc(1, sizeof(t_object));
	if (!*obj)
		return (false);
	if (!init_vec(params[1], &((*obj)->variant.cylinder.pos), 0.0, 0.0)
		|| !init_vec(params[2], &((*obj)->variant.cylinder.dir), -1.0, 1.0)
		|| !init_color(params[5], &((*obj)->variant.cylinder.color)))
		return (free(*obj), *obj = NULL, false);
	(*obj)->variant.cylinder.dir = normalize((*obj)->variant.cylinder.dir);
	(*obj)->variant.cylinder.radius = ft_atof(params[3]) / 2.0;
	(*obj)->variant.cylinder.height = ft_atof(params[4]);
	if ((*obj)->variant.cylinder.radius <= 0.0
		|| (*obj)->variant.cylinder.height <= 0.0)
		return (free(*obj), *obj = NULL, false);
	(*obj)->type = CYLINDER;
	return (true);
}

bool	object_config(const char **params, t_object **obj)
{
	if (!ft_strncmp(*params, "sp", 3) && params_config(params, 3))
		return (sphere_config(params, obj));
	if (!ft_strncmp(*params, "cy", 3) && params_config(params, 5))
		return (cylinder_config(params, obj));
	else if (!ft_strncmp(*params, "pl", 3) && params_config(params, 3))
	{
		*obj = ft_calloc(1, sizeof(t_object));
		if (!*obj)
			return (false);
		if (!init_vec(params[1], &((*obj)->variant.plane.pos), 0.0, 0.0)
			|| !init_vec(params[2]
				, &((*obj)->variant.plane.normal), -1.0, 1.0)
			|| !init_color(params[3], &((*obj)->variant.plane.color)))
			return (free(*obj), *obj = NULL, false);
		return ((*obj)->type = PLANE, true);
	}
	return (false);
}
