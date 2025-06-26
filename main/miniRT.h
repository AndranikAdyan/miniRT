/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:23:52 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/26 19:11:12 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_SIZE 720

# include <unistd.h>
# include <stdlib.h>
# include "mlx.h"
# include "initilization.h"
# include "hooks.h"

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
	void			*mlx;
	void			*window;
	t_data			*img_data;
}	t_mlx;

#endif