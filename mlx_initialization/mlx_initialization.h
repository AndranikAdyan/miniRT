/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initialization.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:46:08 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/20 13:33:53 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INITIALIZATION_H
# define MLX_INITIALIZATION_H

# include "miniRT.h"
# include "scene_types.h"

typedef struct s_mlx	t_mlx;

t_mlx	*init_mlx(char **argv);
int		free_mlx(t_mlx *mlx);

#endif
