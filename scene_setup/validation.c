/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 01:31:03 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/02 19:41:28 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	init_vec(const char *s, t_vector *pos)
{
	char	**param;

	param = ft_split(s, ',');
	if (!param || param_count(param) != VEC_ARG_SIZE)
		return (false);
	pos->x = ft_atof(param[0]);
	pos->y = ft_atof(param[1]);
	pos->z = ft_atof(param[2]);
	return (free_split(&param), true);
}

double	ft_atof(const char *s)
{
	double	param[4];

	param[0] = 0;
	param[1] = 0;
	param[2] = 0;
	param[3] = 1;
	if (s && *s == '+' || *s == '-')
		param[3] = (double)((*s == '+') - (*s++ == '-'));
	while (s && *s)
	{
		if (ft_isdigit(*s))
		{
			param[0] = param[0] * 10.0 + (double)(*s - '0');
			if (param[2])
				++param[1];
		}
		else if (*s == '.' && !param[2])
			param[2] = 1.0;
		else
			return (0.0);
		++s;
	}
	param[0] *= param[3];
	return (param[0] / pow(10.0, (int)param[1]));
}

bool	camera_config(t_camera **camera, char **params)
{
	if (params_count(params) != 4 || !params_config(params, CAM_ARG_SIZE))
		return (camera = NULL, false);
	*camera = ft_calloc(1, sizeof(t_camera));
	if (!*camera)
		return (false);
	if (!init_vec(param[1], *camera->pos) && !init_vec(param[2], *camera->dir))
		return (free(*camera), *camera = NULL, false);
	*camera->fov = ft_atoi(param[3]);
	return (true);
}
