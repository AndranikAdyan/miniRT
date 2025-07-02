/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilization.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:46:08 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/26 19:04:01 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITILIZATION_H
# define INITILIZATION_H

# include "miniRT.h"

typedef struct  s_rgb
{
        unsigned char   red;
        unsigned char   green;
        unsigned char   blue;
}   t_rgb;

typedef enum    e_obj_type
{
        SPHERE,
        PLANE,
        CYLINDER,
}       t_obj_type;

typedef struct  s_vec
{
        double  x;
        double  y;
        double  z;
}       t_vec;

typedef struct  s_camera
{
        t_vec   pos;
        t_vec   dir;
        int     fov;
}       t_camera;

typedef struct  s_object
{
        t_obj_type  obj_type;
        t_vec   position;
        t_vec   dir;
        double  radius;
        double  height;
        t_rgb   color;
}       t_object;

typedef struct s_mlx    t_mlx;

t_mlx   *init_mlx(void);
int     free_mlx(t_mlx *mlx);

#endif
