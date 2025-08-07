/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 02:43:19 by saslanya          #+#    #+#             */
/*   Updated: 2025/08/08 01:09:42 by saslanya         ###   ########.fr       */
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
	t_vec	v[2];
	double	proj;

	if (obj->type == SPHERE)
		return (sphere_normalize(&(obj->variant.sphere), &point));
	else if (obj->type == PLANE)
		return (normalize(obj->variant.plane.normal));
	else if (obj->type == CYLINDER)
	{
		v[0] = vec_sub(point, obj->variant.cylinder.pos);
		proj = dot_product(v[0], obj->variant.cylinder.dir);
		v[1] = scalar_product(obj->variant.cylinder.dir, proj);
		return (normalize(vec_sub(v[0], v[1])));
	}
	else if (obj->type == CONE)
	{
		proj = vec_length(vec_sub(point, obj->variant.cone.point)) / sqrt(1
				+ pow(obj->variant.cone.diameter / obj->variant.cone.height,
					2.0));
		v[1] = vec_add(obj->variant.cone.point, scalar_product(normalize(
						vec_sub(obj->variant.cone.pos,
							obj->variant.cone.point)), proj));
		return (normalize(vec_sub(point, v[1])));
	}
	return ((t_vec){0, 0, 0});
}

static void	get_texture_color(const t_sphere *sphere, t_hit *hit)
{
	t_vec	p;
	char	*pixel;
	double	uv[2];	
	int		xy[2];

	p = normalize(vec_sub(hit->point, sphere->pos));
	uv[0] = fmax(fmin(0.5 + atan2(p.z, p.x) / (2 * M_PI), 0.99), 0.0);
	uv[1] = fmax(fmin(0.5 - asin(p.y) / M_PI, 0.99), 0.0);
	xy[0] = (int)(uv[0] * (sphere->texture.width - 1));
	xy[1] = (int)(uv[1] * (sphere->texture.height - 1));
	pixel = sphere->texture.addr + xy[1] * sphere->texture.line_length
		+ xy[0] * (sphere->texture.bits_per_pixel / 8);
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
	else if (figure->type == SPHERE && figure->variant.sphere.bump_mode)
		get_texture_color(&(figure->variant.sphere), hit);
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
