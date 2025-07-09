/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:55:41 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/09 17:26:20 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

int	rgb_to_int(t_rgb *color)
{
	if (!color)
		return (0);
	return ((color->red << 16) | (color->green << 8) | color->blue);
}

void	draw_pixel(int x, int y, t_data *img, int color)
{
	char	*pixel_addr;

	if (x < 0 || y < 0 || x >= WIN_WEIGHT || y >= WIN_HEIGHT)
		return ;
	pixel_addr = img->addr + (y * img->line_length + x * \
		(img->bits_per_pixel / 8));
	*(unsigned int *)pixel_addr = color;
}

t_rgb	*calculate_color(t_scene *scene, double x, double y)
{
	double		min;
	double		tmp_min;
	t_rgb		*color;
	t_list		*obj_list;

	color = NULL;
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
				color = &(((t_object *)obj_list->content)
						->variant.sphere.color);
			}
		}
		obj_list = obj_list->next;
	}
	return (color);
}

void	draw_objects(t_mlx *mlx)
{
	double	x;
	double	y;
	t_rgb	*color;

	y = 0.0;
	while (y < WIN_HEIGHT)
	{
		x = 0.0;
		while (x < WIN_WEIGHT)
		{
			color = calculate_color(mlx->scene, x, y);
			draw_pixel((int)x, (int)y, mlx->img_data, rgb_to_int(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img_data->img, 0, 0);
}
