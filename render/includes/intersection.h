/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:09:07 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/23 00:46:36 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include <pthread.h>
# include "miniRT.h"
# include "scene.h"
# include "ray.h"
# include "miniRT.h"
# include "light.h"

# define BACKGORUND_COLOR 0x000000

typedef struct s_hit
{
	bool		intersection;
	t_rgb		color;
	double		distance;
	t_object	*figure;
	t_vec		point;
	t_vec		normal;
}	t_hit;

typedef struct s_render_threads
{
	t_mlx		*mlx;
	pthread_t	thread;
	double		col_start;
	double		row_start;
	double		col_end;
	double		row_end;
}	t_render_threads;

void	intersection_with_object(t_scene *scene, t_object *figure,
			t_hit *hit, double *xy);
void	intersection_with_light(t_scene *scene, t_light *light, t_hit *hit);
void	*draw_frame(void *data);
void	set_hit_values(t_hit *hit, t_rgb color,
			t_object *figure, t_vec point);
double	intersection_sphere(t_scene *scene,
			t_sphere *sphere, double x, double y);
double	intersection_plane(t_scene *scene,
			t_plane *plane, double x, double y);
double	intersection_cylinder(t_scene *scene,
			t_cylinder *cy, double x, double y);
double	intersection_cone(t_scene *scene,
			t_cone *cone, double x, double y);

#endif
