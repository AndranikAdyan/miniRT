/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:09:07 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/11 12:58:31 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "miniRT.h"
# include "scene.h"
# include "ray.h"
# include "miniRT.h"

# define BACKGORUND_COLOR 0x000000

typedef struct s_hit
{
	bool		intersection;  // hatum ka te che
	int			color; // pixeli veradarcvox guyn
	double		distance; // jaragaytic minchev hatman ket heravorytun
	t_object	*figure;  // en  firgur@ vori het hatvel enq (normal u mnacac hashvarkneri hamar)
	t_vec		point;    // hatman kkordinatner
	t_vec		normal;   // ketic u obyketic kaxvac normal


}	t_hit;

void	intersection_with_object(t_scene *scene, t_object *figure,
			t_hit *hit,  double *xy);
void	intersection_with_light(t_scene *scene, t_light *light, t_hit *hit);
void	draw_frame(t_mlx *mlx);

#endif
