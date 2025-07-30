/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:41:15 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/30 15:18:52 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_config.h"

t_mlx	*init_mlx(char **argv)
{
	t_mlx	*mlx;
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (perror("Memory allocation failed for scene"), NULL);
	if (!load_scene(argv[1], scene))
		return (printf("Failed to load scene.\n"), free_scene(&scene), NULL);
	mlx = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return (free_scene(&scene), NULL);
	mlx->img_data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!mlx->img_data)
		return (free(mlx), free_scene(&scene), NULL);
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, WIN_WEIGHT, WIN_HEIGHT, "MiniRT");
	mlx->img_data->img = mlx_new_image(mlx->mlx, WIN_WEIGHT, WIN_HEIGHT);
	mlx->img_data->addr = mlx_get_data_addr(mlx->img_data->img,
			&mlx->img_data->bits_per_pixel,
			&mlx->img_data->line_length, &mlx->img_data->endian);
	return (mlx->scene = scene, mlx);
}

int	free_mlx(t_mlx *mlx)
{
	t_list		*iter;
	t_object	*obj;

	mlx_destroy_image(mlx->mlx, mlx->img_data->img);
	mlx_destroy_window(mlx->mlx, mlx->window);
	free(mlx->img_data);
	iter = mlx->scene->objects;
	while (iter)
	{
		obj = (t_object *)iter->content;
		if (obj->type == SPHERE && obj->variant.sphere.texture.is_valid)
			mlx_destroy_image(mlx->mlx, obj->variant.sphere.texture.img);
		iter = iter->next;
	}
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free_scene(&mlx->scene);
	free(mlx);
	exit(EXIT_SUCCESS);
}

static void	set_mode(t_hit *hit)
{
	if (hit->figure->type == CYLINDER)
		hit->figure->variant.cylinder.board_mode
			= !hit->figure->variant.cylinder.board_mode;
	if (hit->figure->type == SPHERE
		&& hit->figure->variant.sphere.texture.is_valid)
		hit->figure->variant.sphere.bump_mode
			= !hit->figure->variant.sphere.bump_mode;
}

int	mouse_click(int button, int x, int y, void *param)
{
	t_mlx	*mlx;
	t_hit	hit;
	t_list	*iter;

	mlx = (t_mlx *)param;
	ft_bzero(&hit, sizeof(t_hit));
	hit.distance = INFINITY;
	iter = mlx->scene->objects;
	while (iter)
	{
		intersection_with_object(mlx->scene, (t_object *)iter->content,
			&hit, (double []){x, y});
		iter = iter->next;
	}
	if (hit.intersection)
	{
		set_mode(&hit);
		if (multi_rendering(mlx, -1))
			mlx_put_image_to_window(mlx->mlx, mlx->window,
				mlx->img_data->img, 0, 0);
	}
	return ((void)button, 0);
}

int	keys_handle(int keycode, t_mlx *mlx)
{
	if (keycode == XK_Escape || keycode == XK_q)
		free_mlx(mlx);
	return (0);
}
