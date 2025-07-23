/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:12:28 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/24 02:13:26 by saslanya         ###   ########.fr       */
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

static double	cone_shadow(t_vec origin, t_vec dir, t_cone *cone)
{
	t_vec	v;
	double	discriminant;
	double	t[2];
	double	val[5];

	v = vec_sub(origin, cone->pos);
	val[0] = pow(cone->radius / cone->height, 2.0);
	val[1] = dot_product(dir, cone->dir);
	val[2] = dot_product(v, cone->dir);
	val[3] = dot_product(dir, dir) - (1 + val[0]) * val[1] * val[1];
	val[4] = 2 * (dot_product(v, dir) - (1 + val[0]) * val[1] * val[2]);
	discriminant = val[4] * val[4] - 4 * val[3]
		* (dot_product(v, v) - (1 + val[0]) * val[2] * val[2]);
	if (discriminant < 0.0)
		return (INFINITY);
	t[0] = (-val[4] - sqrt(discriminant)) / (2 * val[3]);
	if (t[0] >= 0.001
		&& check_cone_height(cone, origin, dir, t[0]) != INFINITY)
		return (t[0]);
	t[1] = (-val[4] + sqrt(discriminant)) / (2 * val[3]);
	if (t[1] >= 0.001
		&& check_cone_height(cone, origin, dir, t[1]) != INFINITY)
		return (t[1]);
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

double	find_hit(t_list *iter, t_vec hit_point, t_vec dir_to_light)
{
	if (((t_object *)iter->content)->type == SPHERE)
		return (sphere_shadow(hit_point, dir_to_light,
				&((t_object *)iter->content)->variant.sphere));
	else if (((t_object *)iter->content)->type == PLANE)
		return (plane_shadow(hit_point, dir_to_light,
				&((t_object *)iter->content)->variant.plane));
	else if (((t_object *)iter->content)->type == CYLINDER)
		return (cylinder_shadow(hit_point, dir_to_light,
				&((t_object *)iter->content)->variant.cylinder));
	else if (((t_object *)iter->content)->type == CONE)
		return (cone_shadow(hit_point, dir_to_light,
				&((t_object *)iter->content)->variant.cone));
	else
		return (INFINITY);
}
