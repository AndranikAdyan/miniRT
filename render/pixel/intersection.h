/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:09:07 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/09 01:25:48 by aadyan           ###   ########.fr       */
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
t_rgb	*calculate_color(t_scene *scene, double x, double y);
void	draw_objects(t_mlx *mlx);


#endif