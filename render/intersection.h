/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:09:07 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/11 11:59:48 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "miniRT.h"
# include "scene.h"
# include "ray.h"
# include "miniRT.h"

t_rgb	intersection(t_scene *scene, t_list *obj_list,
			double *min, double *xy);
void	draw_frame(t_mlx *mlx);

#endif
