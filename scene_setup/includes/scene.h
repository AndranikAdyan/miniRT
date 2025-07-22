/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:35:18 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/22 12:40:26 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <math.h>
# include "scene_types.h"
# include "get_next_line.h"

# define FFORMAT ".rt"
# define FSIZE 4
# define VEC_ARG_SIZE 3

// EOTF - OETF
double	eotf(double val);
double	oetf(double val);
int		linear_to_gammaint(t_rgb *color);

// Validation part
size_t	params_count(const char **params);
bool	params_config(const char **param, size_t mand_count);
bool	data_analysis(t_scene *scene);
// Some utils part
bool	is_valid_f(const char *fname);
void	free_split(char ***s);
double	ft_atof(const char *arg);
bool	between_range(double value, double min, double max);
bool	init_vec(const char *s, t_vec *pos, double min, double max);
bool	init_color(const char *s, t_rgb *color);
// scene loader part BUILDER PATTERN
void	free_scene(t_scene **scene);
bool	light_config(const char **params, t_light **light);
bool	camera_config(const char **params, t_camera **camera);
bool	object_config(const char **params, t_object **obj);
bool	load_scene(const char *filename, t_scene *scene);

#endif
