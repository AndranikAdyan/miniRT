/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:55:38 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/26 19:06:54 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

typedef struct s_mlx	t_mlx;

# include "miniRT.h"
# include <X11/keysym.h>

void	hooks(t_mlx *mlx);
int		keys_handle(int keycode, t_mlx *mlx);

#endif