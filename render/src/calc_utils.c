/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:53:18 by saslanya          #+#    #+#             */
/*   Updated: 2025/08/08 01:20:21 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

bool	cone_calculations(t_scene *scene, t_cone *cone,
			double *t, t_vec ray)
{
	double	abc[3];
	t_vec	tmp_vecs[3];
	double	vars[4];

	vars[0] = cone->diameter / cone->height;
	vars[0] = vars[0] * vars[0];
	tmp_vecs[0] = vec_sub(scene->camera->pos, cone->pos);
	vars[1] = dot_product(ray, cone->dir);
	vars[2] = dot_product(tmp_vecs[0], cone->dir);
	tmp_vecs[1] = vec_sub(ray, scalar_product(cone->dir, vars[1]));
	tmp_vecs[2] = vec_sub(tmp_vecs[0], scalar_product(cone->dir, vars[2]));
	abc[0] = dot_product(tmp_vecs[1], tmp_vecs[1])
		- vars[0] * vars[1] * vars[1];
	abc[1] = 2 * (dot_product(tmp_vecs[1], tmp_vecs[2])
			- vars[0] * vars[1] * vars[2]);
	abc[2] = dot_product(tmp_vecs[2], tmp_vecs[2])
		- vars[0] * vars[2] * vars[2];
	vars[3] = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (vars[3] < 0)
		return (false);
	t[0] = (-abc[1] - sqrt(vars[3])) / (2 * abc[0]);
	t[1] = (-abc[1] + sqrt(vars[3])) / (2 * abc[0]);
	return (true);
}

double	cone_short_distance(t_vec ray_dir, t_vec ray_origin,
	t_cone *cone, double t[2])
{
	t_vec	axis;
	t_vec	p;
	double	m;
	double	best_t;
	int		i;

	axis = normalize(cone->dir);
	best_t = INFINITY;
	i = 0;
	while (i < 2)
	{
		if (t[i] > 0)
		{
			p = vec_add(ray_origin, scalar_product(ray_dir, t[i]));
			m = dot_product(vec_sub(p, cone->pos), axis);
			if (m >= 0 && m <= cone->height && t[i] < best_t)
				best_t = t[i];
		}
		++i;
	}
	return (best_t);
}

static double	get_pheight(t_texture *tex, int x, int y)
{
	t_rgb	color;
	char	*pixel;

	if (x < 0)
		x = 0;
	else if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	else if (y >= tex->height)
		y = tex->height - 1;
	pixel = tex->addr + y * tex->line_length + x * (tex->bits_per_pixel / 8);
	color.red = pixel[2] & 0xFF;
	color.green = pixel[1] & 0xFF;
	color.blue = pixel[0] & 0xFF;
	return ((color.red + color.green + color.blue) / (3.0 * 255.0));
}

static double	get_bump_height(t_texture *tex, double u, double v)
{
	double	args[4];
	double	h[6];
	int		args2[4];

	args[0] = fmod(u, 1.0) * (tex->width - 1);
	args[1] = fmod(v, 1.0) * (tex->height - 1);
	if (args[0] < 0)
		args[0] += tex->width - 1;
	if (args[1] < 0)
		args[1] += tex->height - 1;
	args2[0] = (int)floor(args[0]);
	args2[1] = (args2[0] + 1) % tex->width;
	args2[2] = (int)floor(args[1]);
	args2[3] = (args2[2] + 1) % tex->height;
	args[2] = args[0] - args2[0];
	args[3] = args[1] - args2[2];
	h[0] = get_pheight(tex, args2[0], args2[2]);
	h[1] = get_pheight(tex, args2[1], args2[2]);
	h[2] = get_pheight(tex, args2[0], args2[3]);
	h[3] = get_pheight(tex, args2[1], args2[3]);
	h[4] = h[0] * (1 - args[2]) + h[1] * args[2];
	h[5] = h[2] * (1 - args[2]) + h[3] * args[2];
	return (h[4] * (1 - args[3]) + h[4] * args[3]);
}

t_vec	sphere_normalize(t_sphere *sphere, const t_vec *hit_point)
{
	double	pms[3];
	t_vec	p;
	t_vec	vecs[3];
	double	height[3];

	p = normalize(vec_sub(*hit_point, sphere->pos));
	if (!sphere->bump_mode || !sphere->bump.is_valid)
		return (p);
	pms[0] = 0.5 + atan2(p.z, p.x) / (2 * M_PI);
	pms[1] = fmax(fmin(0.5 - asin(p.y) / M_PI, 0.99), 0.0);
	height[0] = get_bump_height(&sphere->bump, pms[0], pms[1]);
	height[1] = get_bump_height(&sphere->bump, pms[0] + 0.01, pms[1]);
	height[2] = get_bump_height(&sphere->bump, pms[0], pms[1] + 0.01);
	vecs[0].x = -sin(2 * M_PI * pms[0]);
	vecs[0].y = 0;
	vecs[0].z = cos(2 * M_PI * pms[0]);
	vecs[0] = normalize(vecs[0]);
	vecs[1] = normalize(cross_product(vecs[0], p));
	vecs[2] = vec_add(p, vec_add(
				scalar_product(vecs[0], (height[1] - height[0]) * 3.0),
				scalar_product(vecs[1], (height[2] - height[0]) * 3.0)));
	return (normalize(vecs[2]));
}
