/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:56:04 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/26 19:05:27 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

void	hooks(t_mlx *mlx)
{
	mlx_hook(mlx->window, 2, 1L << 0, keys_handle, mlx);
	mlx_hook(mlx->window, 17, 0, free_mlx, mlx);
}

int	keys_handle(int keycode, t_mlx *mlx)
{
	if (keycode == XK_Escape || keycode == XK_q)
		free_mlx(mlx);
	return (0);
}
