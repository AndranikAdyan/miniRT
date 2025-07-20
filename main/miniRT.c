/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:45:28 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/20 13:26:00 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// bool	is_valid_f(const char *fname)
// {
// 	const char	*iter;

// 	iter = ft_strrchr(fname, '.');
// 	if (iter && !ft_strncmp(iter, FFORMAT, FSIZE))
// 		return (true);
// 	else
// 		return (false);
// }

// bool	validation(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		printf("Usage: %s <scene_file.rt>\n", argv[0]);
// 		return (false);
// 	}
// 	if (!is_valid_f(argv[1]))
// 	{
// 		printf("Invalid file format. Expected .rt file.\n");
// 		return (false);
// 	}
// 	return (true);
// }

// static bool	multi_rendering(t_mlx *mlx, int i)
// {
// 	t_render_threads	*threads;

// 	threads = ft_calloc(THREADS_SIZE, sizeof(t_render_threads));
// 	if (!threads)
// 		return (false);
// 	while (++i < THREADS_SIZE)
// 	{
// 		threads[i].mlx = mlx;
// 		threads[i].col_start = 0;
// 		threads[i].col_end = WIN_WEIGHT;
// 		threads[i].row_start = i * WIN_HEIGHT / THREADS_SIZE;
// 		if (i == THREADS_SIZE -1)
// 			threads[i].row_end = WIN_HEIGHT;
// 		else
// 			threads[i].row_end = (i + 1) * WIN_HEIGHT / THREADS_SIZE;
// 		if (pthread_create(&threads[i].thread, NULL, draw_frame, &threads[i]))
// 		{
// 			while (i)
// 				pthread_join(threads[i--].thread, NULL);
// 			return (free(threads), false);
// 		}
// 	}
// 	while (--i)
// 		pthread_join(threads[i].thread, NULL);
// 	return (free(threads), true);
// }

// int	main(int argc, char **argv)
// {
// 	t_mlx	*mlx;

// 	if (!validation(argc, argv))
// 		return (1);
// 	mlx = init_mlx(argv);
// 	if (!mlx)
// 		return (1);
// 	hooks(mlx);
// 	if (multi_rendering(mlx, -1))
// 		mlx_put_image_to_window(mlx->mlx, mlx->window,
// 			mlx->img_data->img, 0, 0);
// 	printf("Done\n");
// 	mlx_loop(mlx->mlx);
// 	return (0);
// }
