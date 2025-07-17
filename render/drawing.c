/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:47:33 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/17 12:31:29 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

static void	apply_ambient_light(int *color, t_light *ambient)
{
	double	color_result;
	t_rgb	current;

	current.red = (*color >> 16) & 0xFF ;
	current.green = (*color >> 8) & 0xFF;
	current.blue = *color & 0xFF;
	color_result = current.red * ambient->ratio
		* ((double)ambient->color.red / UCHAR_MAX);
	if (color_result > UCHAR_MAX)
		color_result = UCHAR_MAX;
	current.red = (unsigned char)color_result;
	color_result = current.green * ambient->ratio
		* ((double)ambient->color.green / UCHAR_MAX);
	if (color_result > UCHAR_MAX)
		color_result = UCHAR_MAX;
	current.green = (unsigned char)color_result;
	color_result = current.blue * ambient->ratio
		* ((double)ambient->color.blue / UCHAR_MAX);
	if (color_result > UCHAR_MAX)
		color_result = UCHAR_MAX;
	current.blue = (unsigned char)color_result;
	*color = (current.red << 16) | (current.green << 8) | current.blue;
}

static int	get_color(t_scene *scene, double x, double y)
{
	t_list	*iter;
	t_hit	hit;

	iter = scene->objects;
	ft_bzero(&hit, sizeof(t_hit));
	hit.distance = INFINITY;
	while (iter)
	{
		intersection_with_object(scene, (t_object *)iter->content,
			&hit, (double []){x, y});
		iter = iter->next;
	}
	apply_ambient_light(&(hit.color), scene->ambient);
	return (hit.color);
}

void	set_hit_values(t_hit *hit, t_rgb color,
	t_object *figure, t_vec point)
{
	hit->intersection = true;
	hit->color = ((color.red & 0xFF) << 16)
		| ((color.green & 0xFF) << 8) | (color.blue & 0xFF);
	hit->figure = figure;
	hit->point = point;
	hit->normal = (t_vec){0, 0, 0};
}

void	draw_frame(t_mlx *mlx)
{
	double	x;
	double	y;

	y = -1.0;
	while (++y < WIN_HEIGHT)
	{
		x = -1.0;
		while (++x < WIN_WEIGHT)
			*(int *)(mlx->img_data->addr + ((int)y * mlx->img_data->line_length
						+ (int)x * (mlx->img_data->bits_per_pixel / 8)))
				= get_color(mlx->scene, x, y);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img_data->img, 0, 0);
}
