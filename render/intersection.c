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
