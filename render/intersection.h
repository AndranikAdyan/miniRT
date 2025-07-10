/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:09:07 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/11 00:57:04 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "miniRT.h"
# include "scene.h"
# include "ray.h"
# include "miniRT.h"

double	intersection_sphere(t_scene *scene,
		t_sphere *sphere, double x, double y);
double	intersection_plane(t_scene *scene,
	t_plane *plane, double x, double y);
t_rgb	intersection(t_scene *scene, t_list *obj_list,
	double *min, double xy[]);
t_rgb	calculate_color(t_scene *scene, double x, double y);
void	draw_objects(t_mlx *mlx);
void	draw_frame(t_mlx *mlx);
int		rgb_to_int(t_rgb *color);


#endif