/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:18:48 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/23 00:49:58 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

static int	solve_quadratic(double *abc, double *t)
{
	double	discriminant;

	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (0);
	t[0] = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	t[1] = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
	return (1);
}

static double	check_roots(t_vec ray_dir, t_vec ray_origin,
	t_cone *cone, double t[2])
{
	t_vec	axis;
	t_vec	p;
	double	m;
	double	vars[2];
	int		i;

	axis = normalize(cone->dir);
	vars[0] = INFINITY;
	i = 0;
	while (i < 2)
	{
		if (i == 0)
			vars[1] = t[0];
		else
			vars[1] = t[1];
		if (vars[1] > 0)
		{
			p = vec_add(ray_origin, scalar_product(ray_dir, vars[1]));
			m = dot_product(vec_sub(p, cone->point), axis);
			if (m <= 0 && m >= -cone->height && vars[1] < vars[0])
				vars[0] = vars[1];
		}
		i++;
	}
	return (vars[0]);
}

double	intersection_cone(t_scene *scene,
			t_cone *cone, double x, double y)
{
	double	abc[3];
	t_vec	co;
	double	vars[3];
	double	t[2];
	t_vec	ray;

	ray = compute_ray(scene->camera, x, y);
	co = vec_sub(scene->camera->pos, cone->point);
	vars[0] = dot_product(ray, cone->dir);
	vars[1] = dot_product(co, cone->dir);
	vars[2] = tan(atan(cone->radius / cone->height));
	vars[2] = vars[2] * vars[2] + 1;
	abc[0] = dot_product(ray, ray) - vars[2] * (vars[0] * vars[0]);
	abc[1] = 2 * (dot_product(ray, co) - vars[2] * vars[0] * vars[1]);
	abc[2] = dot_product(co, co) - vars[2] * (vars[1] * vars[1]);
	if (!solve_quadratic(abc, t))
		return (INFINITY);
	return (check_roots(ray, scene->camera->pos, cone, t));
}
