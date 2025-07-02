/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:12:45 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/03 00:42:01 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"

# define FFORMAT ".rt"
# define FSIZE 4
# define CAM_ARG_SIZE 3
# define VEC_ARG_SIZE 3

typedef struct  s_rgb
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_rgb;

typedef enum	e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_obj_type;

typedef struct	s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct	s_camera
{
	t_vec	pos;
	t_vec	dir;
	int		fov;
}	t_camera;

typedef struct	s_object
{
	t_obj_type	obj_type;
	t_vec		pos;
	t_vec		dir;
	double		radius;
	double		height;
	t_rgb		color;
}	t_object;

typedef enum	e_light_type
{
	GENERAL_LIGHT,
	AMBIENT_LIGHT,
}	t_light_type;

typedef struct s_light
{
	t_light_type	light_type;
	t_vec			pos;
	double			ratio;
	t_rgb			color;
}	t_light;

void	free_split(char ***s);
bool	is_valid_f(const char *fname);
bool	init_vec(const char *s, t_vec *pos);
bool	init_color(const char *s, t_rgb *color);
bool	params_config(const char **param, size_t mand_count);
size_t	params_count(const char **params);
double	ft_atof(const char *arg);

#endif
