/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:45:28 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/03 20:48:21 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// int	main(int argc, char **argv)
// {
// 	t_camera	camera;
// 	if (argc != 2 || !is_valid_f(*(argv + 1)))
// 		return (EXIT_FAILURE);
// 	camera.dir = (t_vec){0, 0, 1};
// 	camera.pos = (t_vec){0, 0, 0};
// 	camera.fov = 60;
// 	t_vec ray = compute_ray(&camera, 0, 0);
// 	printf("x->%lf\ny->%lf\nz->%lf\n", ray.x, ray.y, ray.z);
// 	return (EXIT_SUCCESS);
// }

int	main(int argc, char **argv)
{
	if (argc != 2 || !is_valid_f(*(argv + 1)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
