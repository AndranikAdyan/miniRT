/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:59:38 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/29 21:22:15 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vectors_formulas.h"
# include "math.h"
# include "mlx_config.h"
# define _USE_MATH_DEFINES

t_vec	compute_ray(t_camera *camera, double x, double y);

#endif
