/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 02:43:19 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/22 12:52:43 by saslanya         ###   ########.fr       */
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
	apply_ambient_light(&(hit.color), scene->ambient);
	apply_spot_lighting(scene, &hit, scene->lights, hit.color);
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

void	set_hit_values(t_hit *hit, t_rgb color,
	t_object *figure, t_vec point)
{
	hit->intersection = true;
	hit->color.red = color.red;
	hit->color.green = color.green;
	hit->color.blue = color.blue;
	hit->figure = figure;
	hit->point = point;
	hit->normal = get_normal(figure, point);
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
