/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:09:09 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/17 00:18:30 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

double	intersection_sphere(t_scene *scene,
		t_sphere *sphere, double x, double y)
{
	t_vec	l;
	t_vec	d;
	double	vars[3];
	double	dis;
	double	t[2];

	d = compute_ray(scene->camera, x, y);
	l = vec_sub(scene->camera->pos, sphere->pos);
	vars[0] = dot_product(d, d);
	vars[1] = 2.0 * dot_product(l, d);
	vars[2] = dot_product(l, l) - (sphere->radius * sphere->radius);
	dis = vars[1] * vars[1] - 4 * vars[0] * vars[2];
	if (dis < 0)
		return (INFINITY);
	t[0] = (-vars[1] - sqrt(dis)) / (2.0 * vars[0]);
	t[1] = (-vars[1] + sqrt(dis)) / (2.0 * vars[0]);
	if (t[0] > 0.001 && t[1] > 0.001)
		return (fmin(t[0], t[1]));
	else if (t[0] > 0.001)
		return (t[0]);
	else if (t[1] > 0.001)
		return (t[1]);
	return (INFINITY);
}

double	intersection_plane(t_scene *scene,
		t_plane *plane, double x, double y)
{
	double	denom;
	t_vec	diff;
	double	t;
	t_vec	ray;

	ray = compute_ray(scene->camera, x, y);
	denom = dot_product(plane->normal, ray);
	if (fabs(denom) < 1e-6)
		return (INFINITY);
	diff = vec_sub(plane->pos, scene->camera->pos);
	t = dot_product(diff, plane->normal) / denom;
	if (t >= 0)
		return (t);
	return (INFINITY);
}

static double	get_discriminant(t_vec ray, t_vec oc, t_vec axis, double radius)
{
	t_vec	d_cross_a;
	t_vec	oc_cross_a;
	double	vars[3];
	double	discriminant;

	d_cross_a = cross_product(ray, axis);
	oc_cross_a = cross_product(oc, axis);
	vars[0] = dot_product(d_cross_a, d_cross_a);
	vars[1] = 2.0 * dot_product(d_cross_a, oc_cross_a);
	vars[2] = dot_product(oc_cross_a, oc_cross_a) - radius * radius;
	discriminant = vars[1] * vars[1] - 4.0 * vars[0] * vars[2];
	return (discriminant);
}

static double	check_height(t_cylinder *cy, t_vec cam_pos, t_vec ray, double t)
{
	t_vec	p;
	t_vec	v;
	double	h;

	p = vec_add(cam_pos, scalar_product(ray, t));
	v = vec_sub(p, cy->pos);
	h = dot_product(v, cy->dir);
	if (h >= 0 && h <= cy->height)
		return (t);
	return (INFINITY);
}

double	intersection_cylinder(t_scene *scene, t_cylinder *cy,
	double x, double y)
{
	t_vec	ray;
	t_vec	oc;
	double	discriminant;
	double	t[2];
	double	tmp;

	ray = normalize(compute_ray(scene->camera, x, y));
	oc = vec_sub(scene->camera->pos, cy->pos);
	discriminant = get_discriminant(ray, oc, cy->dir, cy->radius);
	if (discriminant < 0)
		return (INFINITY);
	t[0] = (-2.0 * dot_product(cross_product(ray, cy->dir),
				cross_product(oc, cy->dir)) - sqrt(discriminant))
		/ (2.0 * dot_product(cross_product(ray, cy->dir),
				cross_product(ray, cy->dir)));
	t[1] = (-2.0 * dot_product(cross_product(ray, cy->dir),
				cross_product(oc, cy->dir)) + sqrt(discriminant))
		/ (2.0 * dot_product(cross_product(ray, cy->dir),
				cross_product(ray, cy->dir)));
	tmp = check_height(cy, scene->camera->pos, ray, t[0]);
	if (tmp != INFINITY)
		return (tmp);
	tmp = check_height(cy, scene->camera->pos, ray, t[1]);
	return (tmp);
}
