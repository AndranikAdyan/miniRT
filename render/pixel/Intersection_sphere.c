/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:09:09 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/09 17:27:55 by aadyan           ###   ########.fr       */
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
	else
		return (INFINITY);
}
