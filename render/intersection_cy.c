/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:18:48 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/23 00:50:43 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

static double	get_discriminant(t_vec ray, t_vec oc, t_vec axis, double r)
{
	t_vec	dc;
	t_vec	ocx;
	double	a;
	double	b;
	double	c;

	dc = cross_product(ray, axis);
	ocx = cross_product(oc, axis);
	a = dot_product(dc, dc);
	b = 2.0 * dot_product(dc, ocx);
	c = dot_product(ocx, ocx) - r * r;
	return (b * b - 4 * a * c);
}

static double	check_height(t_cylinder *cy, t_vec cam, t_vec ray, double t)
{
	t_vec	p;
	double	h;

	p = vec_add(cam, scalar_product(ray, t));
	h = dot_product(vec_sub(p, cy->pos), cy->dir);
	if (h >= 0 && h <= cy->height)
		return (t);
	return (INFINITY);
}

static double	intersect_disk(t_vec ray, t_vec center, t_vec cam,
	t_cylinder *cy)
{
	double	denom;
	double	t;
	t_vec	p;

	denom = dot_product(ray, cy->dir);
	if (fabs(denom) < 1e-6)
		return (INFINITY);
	t = dot_product(vec_sub(center, cam), cy->dir) / denom;
	if (t < 0)
		return (INFINITY);
	p = vec_add(cam, scalar_product(ray, t));
	if (vec_length(vec_sub(p, center)) > cy->radius)
		return (INFINITY);
	return (t);
}

static double	intersect_body(t_cylinder *cy, t_vec ray, t_vec cam)
{
	t_vec	oc;
	double	d;
	double	t[3];
	double	tmp;

	oc = vec_sub(cam, cy->pos);
	d = get_discriminant(ray, oc, cy->dir, cy->radius);
	if (d < 0)
		return (INFINITY);
	t[0] = (-2.0 * dot_product(cross_product(ray, cy->dir),
				cross_product(oc, cy->dir)) - sqrt(d))
		/ (2.0 * dot_product(cross_product(ray, cy->dir),
				cross_product(ray, cy->dir)));
	t[1] = (-2.0 * dot_product(cross_product(ray, cy->dir),
				cross_product(oc, cy->dir)) + sqrt(d))
		/ (2.0 * dot_product(cross_product(ray, cy->dir),
				cross_product(ray, cy->dir)));
	t[2] = INFINITY;
	tmp = check_height(cy, cam, ray, t[0]);
	if (tmp < t[2])
		t[2] = tmp;
	tmp = check_height(cy, cam, ray, t[1]);
	if (tmp < t[2])
		t[2] = tmp;
	return (t[2]);
}

double	intersection_cylinder(t_scene *s, t_cylinder *cy, double x, double y)
{
	t_vec	ray;
	t_vec	cam;
	t_vec	top;
	double	t_final;
	double	t_disk;

	cam = s->camera->pos;
	ray = compute_ray(s->camera, x, y);
	t_final = intersect_body(cy, ray, cam);
	top = vec_add(cy->pos, scalar_product(cy->dir, cy->height));
	t_disk = intersect_disk(ray, cy->pos, cam, cy);
	if (t_disk < t_final)
		t_final = t_disk;
	t_disk = intersect_disk(ray, top, cam, cy);
	if (t_disk < t_final)
		t_final = t_disk;
	return (t_final);
}
