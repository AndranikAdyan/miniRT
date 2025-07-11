/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:47:33 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/11 13:49:07 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

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
	if (!hit.intersection)
		return (BACKGORUND_COLOR);
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

void	intersection_with_object(t_scene *scene, t_object *figure,
			t_hit *hit, double *xy)
{
	double	tmp_min;
	t_rgb	color;

	if (figure->type == SPHERE)
	{
		tmp_min = intersection_sphere(scene,
				&figure->variant.sphere, xy[0], xy[1]);
		color = figure->variant.sphere.color;
	}
	else if (figure->type == PLANE)
	{
		tmp_min = intersection_plane(scene,
				&figure->variant.plane, xy[0], xy[1]);
		color = figure->variant.plane.color;
	}
	else
	{
		tmp_min = INFINITY;
		color = (t_rgb){0, 0, 0};
	}
	if (tmp_min < hit->distance)
	{
		hit->distance = tmp_min;
		set_hit_values(hit, color, figure, (t_vec){xy[0], xy[1], tmp_min});
	}
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
