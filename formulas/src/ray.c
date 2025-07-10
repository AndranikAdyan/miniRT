/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:59:36 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/09 17:27:09 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_vec	compute_ray(t_camera *camera, double x, double y)
{
	double	aspect_ratio;
	double	fov_rad;
	double	px;
	double	py;

	aspect_ratio = (double)WIN_WEIGHT / (double)WIN_HEIGHT;
	fov_rad = tan((camera->fov * M_PI / 180.0) / 2.0);
	px = (2.0 * (x + 0.5) / WIN_WEIGHT - 1.0) * aspect_ratio * fov_rad;
	py = (1.0 - 2.0 * (y + 0.5) / WIN_HEIGHT) * fov_rad;
	return (normalize(vec_add(
				camera->dir,
				vec_add(
					scalar_product(
						normalize(cross_product(camera->dir, (t_vec){0, 1, 0})),
					px),
				scalar_product(
					normalize(cross_product(
							normalize(cross_product(camera->dir,
									(t_vec){0, 1, 0})),
						camera->dir)),
				py)))));
}
