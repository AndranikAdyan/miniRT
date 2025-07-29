/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:09:07 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/29 22:00:06 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include <pthread.h>
# include "mlx.h"
# include "scene.h"
# include "ray.h"
# include "light.h"

# define BACKGORUND_COLOR 0x000000

typedef struct s_mlx	t_mlx;

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

// cone utils
bool	cone_calculations(t_scene *scene, t_cone *cone,
			double *t, t_vec ray);
double	cone_short_distance(t_vec ray_dir, t_vec ray_origin,
			t_cone *cone, double t[2]);
// cylinder cylinde_utils
double	get_discriminant(t_vec ray, t_vec oc, t_vec axis, double r);
double	check_height(t_cylinder *cy, t_vec cam, t_vec ray, double t);
double	intersect_disk(t_vec ray, t_vec center, t_vec cam, t_cylinder *cy);
double	intersect_body(t_cylinder *cy, t_vec ray, t_vec cam);
void	get_cy_color(t_cylinder *cy, t_hit *hit);

void	intersection_with_object(t_scene *scene, t_object *figure,
			t_hit *hit, double *xy);
void	intersection_with_light(t_scene *scene, t_light *light, t_hit *hit);
void	*draw_frame(void *data);
void	set_hit_values(t_hit *hit, t_rgb color,
			t_object *figure, t_vec point);
#endif
