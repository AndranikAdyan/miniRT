/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:45:28 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/17 12:29:51 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	is_valid_f(const char *fname)
{
	const char	*iter;

	iter = ft_strrchr(fname, '.');
	if (iter && !ft_strncmp(iter, FFORMAT, FSIZE))
		return (true);
	else
		return (false);
}

bool	validation(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <scene_file.rt>\n", argv[0]);
		return (false);
	}
	if (!is_valid_f(argv[1]))
	{
		printf("Invalid file format. Expected .rt file.\n");
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (!validation(argc, argv))
		return (1);
	mlx = init_mlx(argv);
	if (!mlx)
		return (1);
	hooks(mlx);
	draw_frame(mlx);
	printf("Done\n");
	mlx_loop(mlx->mlx);
	return (0);
}
