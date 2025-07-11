/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initialization.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:46:08 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/09 17:10:24 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITILIZATION_H
# define INITILIZATION_H

# include "miniRT.h"
# include "scene_types.h"

typedef struct s_mlx	t_mlx;

t_mlx	*init_mlx(char **argv);
int		free_mlx(t_mlx *mlx);

#endif
