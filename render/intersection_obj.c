/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:20:36 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/20 02:57:24 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

static t_rgb	handle_sphere(t_scene *scene, t_object *obj,
	double *tmp_min, double *xy)
{
	*tmp_min = intersection_sphere(scene,
			&obj->variant.sphere, xy[0], xy[1]);
	return (obj->variant.sphere.color);
}

static t_rgb	handle_plane(t_scene *scene, t_object *obj,
	double *tmp_min, double *xy)
{
	*tmp_min = intersection_plane(scene,
			&obj->variant.plane, xy[0], xy[1]);
	return (obj->variant.plane.color);
}

static t_rgb	handle_cylinder(t_scene *scene, t_object *obj,
	double *tmp_min, double *xy)
{
	*tmp_min = intersection_cylinder(scene,
			&obj->variant.cylinder, xy[0], xy[1]);
	return (obj->variant.cylinder.color);
}

void	intersection_with_object(t_scene *scene,
		t_object *obj, t_hit *hit, double *xy)
{
	double	tmp_min;
	t_rgb	color;
	t_vec	ray_dir;
	t_vec	hit_point;

	if (obj->type == SPHERE)
		color = handle_sphere(scene, obj, &tmp_min, xy);
	else if (obj->type == PLANE)
		color = handle_plane(scene, obj, &tmp_min, xy);
	else if (obj->type == CYLINDER)
		color = handle_cylinder(scene, obj, &tmp_min, xy);
	else
	{
		tmp_min = INFINITY;
		color = (t_rgb){0, 0, 0};
	}
	if (tmp_min < hit->distance)
	{
		ray_dir = compute_ray(scene->camera, xy[0], xy[1]);
		hit_point = vec_add(scene->camera->pos,
				scalar_product(ray_dir, tmp_min));
		hit->distance = tmp_min;
		set_hit_values(hit, color, obj, hit_point);
	}
}
