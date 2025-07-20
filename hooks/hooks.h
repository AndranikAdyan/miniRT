/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:55:38 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/20 13:34:12 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "miniRT.h"
# include <X11/keysym.h>

typedef struct s_mlx	t_mlx;

void	hooks(t_mlx *mlx);
int		keys_handle(int keycode, t_mlx *mlx);

#endif