/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:46:10 by aadyan            #+#    #+#             */
/*   Updated: 2025/06/26 19:03:56 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initilization.h"

t_mlx	*init_mlx(void)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->img_data = (t_data *)malloc(sizeof(t_data));
	if (!mlx->img_data)
		return (free(mlx), NULL);
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, WIN_SIZE, WIN_SIZE, "Fract-ol");
	mlx->img_data->img = mlx_new_image(mlx->mlx, WIN_SIZE, WIN_SIZE);
	mlx->img_data->addr = mlx_get_data_addr(mlx->img_data->img, \
						&mlx->img_data->bits_per_pixel, \
						&mlx->img_data->line_length, &mlx->img_data->endian);
	return (mlx);
}

int	free_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img_data->img);
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free(mlx->img_data);
	free(mlx);
	exit(0);
}
