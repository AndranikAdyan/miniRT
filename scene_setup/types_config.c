/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 01:40:38 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/04 01:54:19 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	light_config(const char **params, t_light **light)
{
	int	pos_index;

	if (!params_config(params, 2)
		&& !params_config(params, 3))
		return (*light = NULL, false);
	pos_index = !ft_strncmp(params[0], "A", 2) + 1;
	*light = ft_calloc(1, sizeof(t_light));
	if (!*light)
		return (false);
	if (!init_vec(params[pos_index], &(*light)->pos))
		return (free(*light), *light = NULL, false);
	(*light)->ratio = ft_atof(params[pos_index == 1]);
	(*light)->type = LIGHT;
	if (pos_index != 1)
		(*light)->type = AMBIENT;
	if (params[2] && !init_color(params[2], &(*light)->color))
		return (free(*light), *light = NULL, !params[2]);
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
