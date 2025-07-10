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

t_rgb	calculate_color(t_scene *scene, double x, double y)
{
	double		min;
	double		tmp_min;
	t_rgb		color;
	t_list		*obj_list;

	color = (t_rgb){0, 0, 0};
	min = INFINITY;
	obj_list = scene->objects;
	while (obj_list)
	{
		if (((t_object *)obj_list->content)->type == SPHERE)
		{
			tmp_min = intersection_sphere(scene,
					&(((t_object *)obj_list->content)->variant.sphere), x, y);
			if (tmp_min < min)
			{
				min = tmp_min;
				color = (((t_object *)obj_list->content)
						->variant.sphere.color);
			}
		}
		obj_list = obj_list->next;
	}
	return (color);
}

void	draw_frame(t_mlx *mlx)
{
	double	x;
	double	y;
	t_rgb	color;

	y = -1.0;
	while (++y < WIN_HEIGHT)
	{
		x = -1.0;
		while (++x < WIN_WEIGHT)
		{
			color = calculate_color(mlx->scene, x, y);
			*(int *)(mlx->img_data->addr + ((int)y * mlx->img_data->line_length
						+ (int)x * (mlx->img_data->bits_per_pixel / 8)))
				= (color.red << 16) | (color.green << 8) | color.blue;
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img_data->img, 0, 0);
}

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
