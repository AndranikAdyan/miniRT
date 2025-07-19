/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:39:32 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/20 02:42:10 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

static double	plane_shadow(const t_vec origin, const t_vec dir
		, t_plane *plane)
{
	double	denom;
	double	hit_distance;

	denom = dot_product(plane->normal, dir);
	if (fabs(denom) < 1e-6)
		return (INFINITY);
	hit_distance = dot_product(vec_sub(plane->pos, origin),
			plane->normal) / denom;
	if (hit_distance >= 0.001)
		return (hit_distance);
	else
		return (INFINITY);
}

static double	sphere_shadow(const t_vec origin, const t_vec dir,
		t_sphere *sphere)
{
	t_vec		oc;
	double		abc[3];
	double		discriminant;
	double		hit_distance;

	oc = vec_sub(origin, sphere->pos);
	abc[0] = dot_product(dir, dir);
	abc[1] = 2.0 * dot_product(oc, dir);
	abc[2] = dot_product(oc, oc) - sphere->radius * sphere->radius;
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0.0)
		return (INFINITY);
	hit_distance = (-abc[1] - sqrt(discriminant)) / (2.0 * abc[0]);
	if (hit_distance > 0.001)
		return (hit_distance);
	hit_distance = (-abc[1] + sqrt(discriminant)) / (2.0 * abc[0]);
	if (hit_distance > 0.001)
		return (hit_distance);
	return (INFINITY);
}

static double	check_height_shadow(t_cylinder *cy, t_vec origin,
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

static double	cylinder_shadow(t_vec origin, t_vec dir, t_cylinder *cy)
{
	t_vec	cross[2];
	double	vars[3];
	double	discriminant;
	double	h;

	cross[0] = cross_product(dir, cy->dir);
	cross[1] = cross_product(vec_sub(origin, cy->pos), cy->dir);
	vars[0] = dot_product(cross[0], cross[0]);
	vars[1] = 2.0 * dot_product(cross[0], cross[1]);
	vars[2] = dot_product(cross[1], cross[1]) - (cy->radius * cy->radius);
	discriminant = vars[1] * vars[1] - 4.0 * vars[0] * vars[2];
	if (discriminant < 0)
		return (INFINITY);
	h = (-vars[1] - sqrt(discriminant)) / (2.0 * vars[0]);
	if (h >= 0.001 && check_height_shadow(cy, origin, dir, h) != INFINITY)
		return (check_height_shadow(cy, origin, dir, h));
	h = (-vars[1] + sqrt(discriminant)) / (2.0 * vars[0]);
	if (h >= 0.001 && check_height_shadow(cy, origin, dir, h) != INFINITY)
		return (check_height_shadow(cy, origin, dir, h));
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
		hit_distance = INFINITY;
		if (((t_object *)iter->content)->type == SPHERE)
			hit_distance = sphere_shadow(hit_point, dir_to_light,
					&((t_object *)iter->content)->variant.sphere);
		else if (((t_object *)iter->content)->type == PLANE)
			hit_distance = plane_shadow(hit_point, dir_to_light,
					&((t_object *)iter->content)->variant.plane);
		else if (((t_object *)iter->content)->type == CYLINDER)
			hit_distance = cylinder_shadow(hit_point, dir_to_light,
					&((t_object *)iter->content)->variant.cylinder);
		if (hit_distance > 0.001 && hit_distance < dist_to_light)
			return (true);
		iter = iter->next;
	}
	return (false);
}
