/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_calcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 00:59:33 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/26 22:28:10 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

double	get_discriminant(t_vec ray, t_vec oc, t_vec axis, double r)
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

double	check_height(t_cylinder *cy, t_vec cam, t_vec ray, double t)
{
	t_vec	p;
	double	h;

	p = vec_add(cam, scalar_product(ray, t));
	h = dot_product(vec_sub(p, cy->pos), cy->dir);
	if (h >= 0 && h <= cy->height)
		return (t);
	return (INFINITY);
}

double	intersect_disk(t_vec ray, t_vec center, t_vec cam,
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
	if (vec_length(vec_sub(p, center)) > cy->diameter)
		return (INFINITY);
	return (t);
}

double	intersect_body(t_cylinder *cy, t_vec ray, t_vec cam)
{
	t_vec	oc;
	double	d;
	double	t[3];
	double	tmp;

	oc = vec_sub(cam, cy->pos);
	d = get_discriminant(ray, oc, cy->dir, cy->diameter);
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

void	get_cy_color(t_cylinder *cy, t_hit *hit)
{
	t_vec	rel;
	double	u;
	double	v;
	double	coeff;

	rel = vec_sub(hit->point, cy->pos);
	u = atan2(rel.z, rel.x) / (2 * M_PI) + 0.5;
	v = dot_product(rel, cy->dir) / cy->height;
	coeff = (double)(((int)(u * 10) + (int)(v * 10)) % 2 == 0);
	hit->color.red = 1.0 * coeff;
	hit->color.green = 1.0 * coeff;
	hit->color.blue = 1.0 * coeff;
}
