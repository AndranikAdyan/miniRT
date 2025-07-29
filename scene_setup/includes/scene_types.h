/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:16:39 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/29 21:57:39 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_TYPES_H
# define SCENE_TYPES_H

# include "libft.h"

# define CAMERA 'C'
# define AMBIENT 'A'
# define LIGHT 'L'
# define SPHERE 's'
# define PLANE 'p'
# define CYLINDER 'c'
# define CONE 'o'

typedef struct s_texture
{
	bool	is_valid;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_rgb
{
	double	red;
	double	green;
	double	blue;
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

typedef struct s_cone
{
	t_vec	pos;
	t_vec	dir;
	t_vec	point;
	double	diameter;
	double	height;
	t_rgb	color;
}	t_cone;

typedef struct s_sphere
{
	t_vec		pos;
	double		diameter;
	int			bump_mode;
	t_rgb		color;
	t_texture	texture;
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
	double	diameter;
	int		board_mode;
	double	height;
	t_rgb	color;
}	t_cylinder;

typedef union u_object_data
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	t_cone		cone;
}	t_object_data;

typedef struct s_object
{
	char			type;
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
	t_light		*ambient;
	t_list		*objects;
	t_list		*lights;
}	t_scene;

#endif
