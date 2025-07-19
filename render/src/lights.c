/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 00:47:11 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/20 03:06:53 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

void	apply_ambient_light(int *color, t_light *ambient)
{
	double	color_result;
	t_rgb	current;

	current.red = (*color >> 16) & 0xFF ;
	current.green = (*color >> 8) & 0xFF;
	current.blue = *color & 0xFF;
	color_result = current.red * ambient->ratio
		* ((double)ambient->color.red / UCHAR_MAX);
	if (color_result > UCHAR_MAX)
		color_result = UCHAR_MAX;
	current.red = (unsigned char)color_result;
	color_result = current.green * ambient->ratio
		* ((double)ambient->color.green / UCHAR_MAX);
	if (color_result > UCHAR_MAX)
		color_result = UCHAR_MAX;
	current.green = (unsigned char)color_result;
	color_result = current.blue * ambient->ratio
		* ((double)ambient->color.blue / UCHAR_MAX);
	if (color_result > UCHAR_MAX)
		color_result = UCHAR_MAX;
	current.blue = (unsigned char)color_result;
	*color = (current.red << 16) | (current.green << 8) | current.blue;
}

static void	set_configs(t_light *light, t_hit *hit,
		t_light_config *config, t_vec ray_dir)
{
	config->light_dir = normalize(vec_sub(light->pos, hit->point));
	config->view_dir = scalar_product(ray_dir, -1);
	config->diff_intensity = fmax(0.0, dot_product(hit->normal,
				config->light_dir)) * light->ratio;
	config->reflect_dir = vec_sub(scalar_product(hit->normal, 2
				* dot_product(hit->normal, config->light_dir)),
			config->light_dir);
	config->spec_intensity = pow(fmax(dot_product(config->view_dir,
					config->reflect_dir), 0.0), 32) * light->ratio;
}

void	apply_spot_lighting(t_scene *scene, t_hit *hit,
		t_list *light_iter, double *rgb)
{
	t_light_config	config;

	while (light_iter)
	{
		if (!shadow(scene, hit->point, ((t_light *)light_iter->content)->pos))
		{
			set_configs((t_light *)light_iter->content, hit, &config,
				normalize(vec_sub(hit->point, scene->camera->pos)));
			rgb[0] += (int)(((hit->color >> 16) & 0xFF)
					* config.diff_intensity + 255 * config.spec_intensity);
			rgb[1] += (int)(((hit->color >> 8) & 0xFF)
					* config.diff_intensity + 255 * config.spec_intensity);
			rgb[2] += (int)((hit->color & 0xFF)
					* config.diff_intensity + 255 * config.spec_intensity);
			if (rgb[0] > (double)UCHAR_MAX)
				rgb[0] = UCHAR_MAX;
			if (rgb[1] > (double)UCHAR_MAX)
				rgb[1] = UCHAR_MAX;
			if (rgb[2] > (double)UCHAR_MAX)
				rgb[2] = UCHAR_MAX;
		}
		light_iter = light_iter->next;
	}
	hit->color = ((int)rgb[0] << 16) | ((int)rgb[1] << 8) | (int)rgb[2];
}
