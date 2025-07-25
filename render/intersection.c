/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:09:09 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/20 23:18:44 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

void	intersection_with_sphere(t_scene *scene, t_object *obj,
			t_hit *hit, t_vec cam_dir)
{
	t_vec	l;
	double	vars[3];
	double	distance;
	double	t[2];

	l = vec_sub(scene->camera->pos, obj->variant.sphere.pos);
	vars[0] = dot_product(cam_dir, cam_dir);
	vars[1] = 2.0 * dot_product(l, cam_dir);
	vars[2] = dot_product(l, l)
		- (obj->variant.sphere.radius * obj->variant.sphere.radius);
	distance = vars[1] * vars[1] - 4 * vars[0] * vars[2];
	if (distance < 0 || distance >= hit->distance)
		return ;
	t[0] = (-vars[1] - sqrt(distance)) / (2.0 * vars[0]);
	t[1] = (-vars[1] + sqrt(distance)) / (2.0 * vars[0]);
	if (t[0] > 0.001 || t[1] > 0.001)
	{
		hit->distance = t[(t[1] > 0.001) && (t[1] < t[0])];
		set_hit_values(hit, obj->variant.sphere.color, obj,
			vec_add(scene->camera->pos,
				scalar_product(cam_dir, hit->distance)));
	}
}

void	intersection_with_plane(t_scene *scene, t_object *obj,
		t_hit *hit, t_vec cam_dir)
{
	double	denom;
	double	t;

	denom = dot_product(obj->variant.plane.normal, cam_dir);
	if (fabs(denom) < 1e-6)
		return ;
	t = dot_product(vec_sub(obj->variant.plane.pos,
				scene->camera->pos),
			obj->variant.plane.normal) / denom;
	if (t >= 0 && t < hit->distance)
	{
		hit->distance = t;
		set_hit_values(hit, obj->variant.plane.color, obj,
			vec_add(scene->camera->pos,
				scalar_product(cam_dir, hit->distance)));
	}
}
