/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:02:59 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/31 15:55:53 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_load.h"

bool	multi_rendering(t_mlx *mlx, int i)
{
	t_render_threads	*threads;

	threads = ft_calloc(THREADS_SIZE, sizeof(t_render_threads));
	if (!threads)
		return (false);
	while (++i < THREADS_SIZE)
	{
		threads[i].mlx = mlx;
		threads[i].col_start = 0;
		threads[i].col_end = WIN_WEIGHT;
		threads[i].row_start = i * WIN_HEIGHT / THREADS_SIZE;
		if (i == THREADS_SIZE - 1)
			threads[i].row_end = WIN_HEIGHT;
		else
			threads[i].row_end = (i + 1) * WIN_HEIGHT / THREADS_SIZE;
		if (pthread_create(&threads[i].thread, NULL, draw_frame, &threads[i]))
		{
			while (i)
				pthread_join(threads[i--].thread, NULL);
			return (free(threads), false);
		}
	}
	while (--i)
		pthread_join(threads[i].thread, NULL);
	return (free(threads), true);
}

static void	hooks(t_mlx *mlx)
{
	mlx_hook(mlx->window, 2, 1L << 0, keys_handle, mlx);
	mlx_hook(mlx->window, 17, 0, free_mlx, mlx);
	mlx_mouse_hook(mlx->window, mouse_click, mlx);
}

static bool	load_texture(void *mlx, const char *path, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(mlx, (char *)path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (false);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	return (true);
}

void	init_textures(t_mlx *mlx)
{
	t_list	*iter;

	iter = mlx->scene->objects;
	while (iter)
	{
		if (((t_object *)iter->content)->type == SPHERE)
		{
			((t_object *)iter->content)->variant.sphere.bump_mode = false;
			if (((t_object *)iter->content)->variant.sphere.format)
				((t_object *)iter->content)->variant.sphere.texture.is_valid
					= load_texture(mlx->mlx,
						((t_object *)iter->content)->variant.sphere.format,
						&((t_object *)iter->content)->variant.sphere.texture);
		}
		iter = iter->next;
	}
}

int	main(int argc, char **argv)
{
	t_mlx			*mlx;

	if (!validation(argc, argv))
		return (EXIT_FAILURE);
	mlx = init_mlx(argv);
	if (!mlx)
		return (EXIT_FAILURE);
	init_textures(mlx);
	hooks(mlx);
	if (multi_rendering(mlx, -1))
		mlx_put_image_to_window(mlx->mlx, mlx->window,
			mlx->img_data->img, 0, 0);
	mlx_loop(mlx->mlx);
	return (EXIT_SUCCESS);
}
