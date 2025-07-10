/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:45:28 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/09 17:10:30 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
