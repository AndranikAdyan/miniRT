/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:47:33 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/11 01:20:24 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

t_rgb	calculate_color(t_scene *scene, double x, double y)
{
	double	min;
	t_rgb	color;
	t_list	*obj_list;
	t_rgb	tmp_color;

	color = (t_rgb){0, 0, 0};
	min = INFINITY;
	obj_list = scene->objects;
	while (obj_list)
	{
		tmp_color = intersection(scene, obj_list, &min, (double []){x, y});
		if (!(tmp_color.red == 0 && tmp_color.green == 0
				&& tmp_color.blue == 0))
			color = tmp_color;
		obj_list = obj_list->next;
	}
	return (color);
}

t_rgb	intersection(t_scene *scene, t_list *obj_list,
	double *min, double xy[])
{
	double	tmp_min;

	if (((t_object *)obj_list->content)->type == SPHERE)
	{
		tmp_min = intersection_sphere(scene,
				&(((t_object *)obj_list->content)->variant.sphere),
				xy[0], xy[1]);
		if (tmp_min < *min)
		{
			*min = tmp_min;
			return (((t_object *)obj_list->content)->variant.sphere.color);
		}
	}
	else if (((t_object *)obj_list->content)->type == PLANE)
	{
		tmp_min = intersection_plane(scene,
				&(((t_object *)obj_list->content)->variant.plane),
				xy[0], xy[1]);
		if (tmp_min < *min)
		{
			*min = tmp_min;
			return (((t_object *)obj_list->content)->variant.plane.color);
		}
	}
	return ((t_rgb){0, 0, 0});
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
