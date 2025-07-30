/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_calcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 00:59:33 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/30 19:22:46 by saslanya         ###   ########.fr       */
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
	t_vec	v[2];
	double	val[3];

	v[0] = vec_sub(hit->point, vec_add(cy->pos,
				scalar_product(cy->dir, cy->height / 2.0)));
	if (fabs(cy->dir.x) > fabs(cy->dir.z))
		v[1] = normalize((t_vec){-cy->dir.y, cy->dir.x, 0});
	else
		v[1] = normalize((t_vec){0, -cy->dir.z, cy->dir.y});
	val[0] = atan2(dot_product(v[0], normalize(cross_product(cy->dir,
						v[1]))), dot_product(v[0], v[1])) / (2 * M_PI);
	if (val[0] < 0)
		val[0] += 1.0;
	val[1] = dot_product(v[0], cy->dir) / cy->height;
	val[0] = fmod(val[0], 1.0);
	if (val[0] < 0)
		val[0] += 1.0;
	val[1] = fmod(val[1], 1.0);
	if (val[1] < 0)
		val[1] += 1.0;
	val[2] = (double)((int)(floor(val[0] * 10) + (int)floor(val[1] * 10)) % 2);
	hit->color.red = val[2];
	hit->color.green = val[2];
	hit->color.blue = val[2];
}
