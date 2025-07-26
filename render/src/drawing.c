/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 02:43:19 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/26 22:27:28 by aadyan           ###   ########.fr       */
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
	if (hit.color.red != 0.0 || hit.color.green != 0.0 || hit.color.blue != 0.0)
	{
		apply_ambient_light(&(hit.color), scene->ambient);
		apply_spot_lighting(scene, &hit, scene->lights, hit.color);
	}
	return (linear_to_gammaint(&(hit.color)));
}

static t_vec	get_normal(t_object *obj, const t_vec point)
{
	t_vec	v;
	t_vec	proj_vec;
	double	proj;

	if (obj->type == SPHERE)
		return (normalize(vec_sub(point, obj->variant.sphere.pos)));
	else if (obj->type == PLANE)
		return (normalize(obj->variant.plane.normal));
	else if (obj->type == CYLINDER)
	{
		v = vec_sub(point, obj->variant.cylinder.pos);
		proj = dot_product(v, obj->variant.cylinder.dir);
		proj_vec = scalar_product(obj->variant.cylinder.dir, proj);
		return (normalize(vec_sub(v, proj_vec)));
	}
	return ((t_vec){0, 0, 0});
}

void	get_texture_color(t_sphere sphere, t_hit *hit)
{
	int		x;
	int		y;
	char	*pixel;

	x = (int)((atan2(hit->normal.z, hit->normal.x) + M_PI)
			/ (2 * M_PI) * (sphere.texture.width - 1));
	y = (int)(acos(hit->normal.y) / M_PI * (sphere.texture.height - 1));
	pixel = sphere.texture.addr + y * sphere.texture.line_length
		+ x * (sphere.texture.bits_per_pixel / 8);
	hit->color.red = (unsigned char)pixel[2] / 255.0;
	hit->color.green = (unsigned char)pixel[1] / 255.0;
	hit->color.blue = (unsigned char)pixel[0] / 255.0;
}

void	set_hit_values(t_hit *hit, t_rgb color,
	t_object *figure, t_vec point)
{
	hit->intersection = true;
	hit->figure = figure;
	hit->point = point;
	hit->normal = get_normal(figure, point);
	if (figure->type == CYLINDER && figure->variant.cylinder.board_mode)
		get_cy_color(&(figure->variant.cylinder), hit);
	else if (figure->type == SPHERE && figure->variant.sphere.bump_mump)
		get_texture_color(figure->variant.sphere, hit);
	else
	{
		hit->color.red = color.red;
		hit->color.green = color.green;
		hit->color.blue = color.blue;
	}
}

void	*draw_frame(void *data)
{
	t_render_threads	*thread_data;
	t_mlx				*mlx;
	double				x;
	double				y;

	thread_data = (t_render_threads *)data;
	mlx = thread_data->mlx;
	y = thread_data->row_start - 1;
	while (++y < thread_data->row_end)
	{
		x = thread_data->col_start - 1;
		while (++x < thread_data->col_end)
			*(int *)(mlx->img_data->addr + ((int)y * mlx->img_data->line_length
						+ (int)x * (mlx->img_data->bits_per_pixel / 8)))
				= get_color(mlx->scene, x, y);
	}
	return (NULL);
}
