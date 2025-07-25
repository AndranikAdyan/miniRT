/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:56:04 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/26 01:53:48 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

#include "intersection.h"
#include "mlx.h"
#include <math.h>

static bool	multi_rendering(t_mlx *mlx, int i)
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
		if (i == THREADS_SIZE -1)
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

staic int	mouse_click(int button, int x, int y, void *param)
{
	t_mlx	*mlx;
	t_hit	hit;
	t_list	*iter;

	*mlx = (t_mlx *)param;
	if (button != 1)
		return (0);
	ft_bzero(&hit, sizeof(t_hit));
	hit.distance = INFINITY;
	iter = mlx->scene->objects;
	while (iter)
	{
		intersection_with_object(mlx->scene, (t_object *)iter->content,
			&hit, (double []){x, y});
		iter = iter->next;
	}
	if (hit.intersection && hit.figure->type == CYLINDER)
		hit.figure->variant.cylinder.board_mode
			= !hit.figure->variant.cylinder.board_mode;
	if (multi_rendering(mlx, -1))
		mlx_put_image_to_window(mlx->mlx, mlx->window,
			mlx->img_data->img, 0, 0);
	return (0);
}

void	hooks(t_mlx *mlx)
{
	mlx_hook(mlx->window, 2, 1L << 0, keys_handle, mlx);
	mlx_hook(mlx->window, 17, 0, free_mlx, mlx);
	mlx_mouse_hook(mlx->window, mouse_click, mlx);
}

int	keys_handle(int keycode, t_mlx *mlx)
{
	if (keycode == XK_Escape || keycode == XK_q)
		free_mlx(mlx);
	return (0);
}
