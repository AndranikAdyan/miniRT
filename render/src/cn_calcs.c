/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_calcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 00:58:40 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/26 00:58:49 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

bool	cone_calculations(t_scene *scene, t_cone *cone,
			double *t, t_vec ray)
{
	double	abc[3];
	t_vec	tmp_vecs[3];
	double	vars[4];

	vars[0] = cone->radius / cone->height;
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
