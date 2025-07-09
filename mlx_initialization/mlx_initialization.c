/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:46:10 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/09 17:10:44 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_initialization.h"

t_mlx	*init_mlx(char **argv)
{
	t_mlx	*mlx;
	t_scene	*scene;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->img_data = (t_data *)malloc(sizeof(t_data));
	if (!mlx->img_data)
		return (free(mlx), NULL);
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, WIN_WEIGHT, WIN_HEIGHT, "MiniRT");
	mlx->img_data->img = mlx_new_image(mlx->mlx, WIN_WEIGHT, WIN_HEIGHT);
	mlx->img_data->addr = mlx_get_data_addr(mlx->img_data->img, \
						&mlx->img_data->bits_per_pixel, \
						&mlx->img_data->line_length, &mlx->img_data->endian);
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (perror("Memory allocation failed for scene"), NULL);
	if (!load_scene(argv[1], scene))
		return (printf("Failed to load scene.\n"), free_scene(&scene), NULL);
	mlx->scene = scene;
	return (mlx);
}

int	free_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img_data->img);
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free(mlx->img_data);
	free_scene(&mlx->scene);
	free(mlx);
	exit(0);
}
