/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:23:52 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/20 03:52:13 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WEIGHT 1080
# define WIN_HEIGHT 720
# define THREADS_SIZE 4
# define _USE_MATH_DEFINES

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "mlx_initialization.h"
# include "hooks.h"
# include "scene.h"
# include "ray.h"
# include "intersection.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	t_data	*img_data;
	t_scene	*scene;
}	t_mlx;

#endif
