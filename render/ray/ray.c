/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:59:36 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/03 20:47:41 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

// t_vec	compute_ray(t_camera *camera, double x, double y)
// {
// 	double	aspect_ratio;
// 	double	fov_rad;
// 	double	px;
// 	double	py;
// 	t_vec	camera_right;
// 	t_vec	camera_up;
// 	t_vec	world_up;
// 	t_vec	right_tmp;
// 	t_vec	up_tmp;
// 	t_vec	tmp1;
// 	t_vec	tmp2;
// 	t_vec	dir;

// 	aspect_ratio = (double)WIN_WEIGHT / (double)WIN_HEIGHT;
// 	fov_rad = tan((camera->fov * M_PI / 180.0) / 2.0);
// 	px = (2.0 * (x + 0.5) / WIN_WEIGHT - 1.0) * aspect_ratio * fov_rad;
// 	py = (1.0 - 2.0 * (y + 0.5) / WIN_HEIGHT) * fov_rad;
// 	world_up = (t_vec){0.0, 1.0, 0.0};
// 	right_tmp = cross_product(&camera->dir, &world_up);
// 	camera_right = normalize(&right_tmp);
// 	up_tmp = cross_product(&camera_right, &camera->dir);
// 	camera_up = normalize(&up_tmp);
// 	tmp1 = scalar_product(&camera_right, px);
// 	tmp2 = scalar_product(&camera_up, py);
// 	tmp1 = vec_add(&tmp1, &tmp2);
// 	dir = vec_add(&camera->dir, &tmp1);
// 	return (normalize(&dir));
// }
