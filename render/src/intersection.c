/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:09:09 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/26 22:28:10 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

static void	intersection_with_sphere(t_scene *scene, t_object *obj,
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
		- (obj->variant.sphere.diameter * obj->variant.sphere.diameter);
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

static void	intersection_with_plane(t_scene *scene, t_object *obj,
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

static void	intersection_with_cylinder(t_scene *scene, t_object *obj,
		t_hit *hit, t_vec cam_dir)
{
	double	t_final;
	double	t[2];

	t_final = intersect_body(&(obj->variant.cylinder),
			cam_dir, scene->camera->pos);
	t[0] = intersect_disk(cam_dir, obj->variant.cylinder.pos,
			scene->camera->pos, &(obj->variant.cylinder));
	t[1] = intersect_disk(cam_dir, vec_add(obj->variant.cylinder.pos,
				scalar_product(obj->variant.cylinder.dir,
					obj->variant.cylinder.height)), scene->camera->pos,
			&(obj->variant.cylinder));
	if (t[0] < t_final || t[1] < t_final)
		t_final = t[t[0] > t[1]];
	if (t_final != INFINITY && t_final < hit->distance)
	{
		hit->distance = t_final;
		set_hit_values(hit, obj->variant.cylinder.color, obj,
			vec_add(scene->camera->pos,
				scalar_product(cam_dir, hit->distance)));
	}
}

static void	intersection_with_cone(t_scene *scene, t_object *obj,
		t_hit *hit, t_vec cam_dir)
{
	double	t[2];

	if (!cone_calculations(scene, &(obj->variant.cone), t, cam_dir))
		return ;
	t[0] = cone_short_distance(cam_dir, scene->camera->pos,
			&(obj->variant.cone), t);
	if (t[0] == INFINITY || t[0] > hit->distance)
		return ;
	hit->distance = t[0];
	set_hit_values(hit, obj->variant.cone.color, obj,
		vec_add(scene->camera->pos,
			scalar_product(cam_dir, hit->distance)));
}

void	intersection_with_object(t_scene *scene,
		t_object *obj, t_hit *hit, double *xy)
{
	if (obj->type == SPHERE)
		intersection_with_sphere(scene, obj, hit,
			compute_ray(scene->camera, xy[0], xy[1]));
	else if (obj->type == PLANE)
		intersection_with_plane(scene, obj, hit,
			compute_ray(scene->camera, xy[0], xy[1]));
	else if (obj->type == CYLINDER)
		intersection_with_cylinder(scene, obj, hit,
			compute_ray(scene->camera, xy[0], xy[1]));
	else if (obj->type == CONE)
		intersection_with_cone(scene, obj, hit,
			compute_ray(scene->camera, xy[0], xy[1]));
}
