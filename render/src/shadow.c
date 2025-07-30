/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:12:50 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/30 18:26:15 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

double	check_cone_height(t_cone *cone, t_vec origin,
			t_vec dir, double t)
{
	t_vec	point;
	double	height;

	point = vec_add(origin, scalar_product(dir, t));
	height = dot_product(vec_sub(point, cone->point), cone->dir);
	if (height >= 0.0 && height <= cone->height)
		return (t);
	return (INFINITY);
}

double	check_height_shadow(t_cylinder *cy, t_vec origin,
		t_vec dir, double t)
{
	double	h;

	h = dot_product(vec_sub(vec_add(origin, scalar_product(dir, t)),
				cy->pos), cy->dir);
	if (h >= 0 && h <= cy->height)
		return (t);
	else
		return (INFINITY);
}

bool	shadow(t_scene *scene, const t_vec hit_point,
		const t_vec light_pos)
{
	t_vec		dir_to_light;
	double		dist_to_light;
	double		hit_distance;
	t_list		*iter;

	dir_to_light = normalize(vec_sub(light_pos, hit_point));
	dist_to_light = vec_length(vec_sub(light_pos, hit_point));
	iter = scene->objects;
	while (iter)
	{
		hit_distance = find_hit(iter, hit_point, dir_to_light);
		if (hit_distance > 0.001 && hit_distance < dist_to_light)
			return (true);
		iter = iter->next;
	}
	return (false);
}
