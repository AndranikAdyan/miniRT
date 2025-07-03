/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:16:39 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/04 01:55:33 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_TYPES_H
# define SCENE_TYPES_H

# include "libft.h"

typedef struct s_rgb
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_rgb;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	dir;
	int		fov;
}	t_camera;

typedef struct s_sphere
{
	t_vec	pos;
	double	radius; // diameter
	t_rgb	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec	pos;
	t_vec	normal;
	t_rgb	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec	pos;
	t_vec	dir;
	double	radius;
	double	height;
	t_rgb	color;
}	t_cylinder;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_object_type;

typedef union u_object_data
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_object_data;

typedef struct s_object
{
	t_object_type	obj_type;
	t_object_data	variant;
}	t_object;

typedef struct s_light
{
	char			type;
	t_vec			pos;
	double			ratio;
	t_rgb			color;
}	t_light;

typedef struct s_scene
{
	t_camera	*camera;
	t_list		*objects;
	t_list		*lights;
}	t_scene;

#endif
