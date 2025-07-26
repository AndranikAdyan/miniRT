/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:13:51 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/26 22:27:12 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

bool	load_texture(void *mlx, char *path, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (NULL);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	return (texture);
}
