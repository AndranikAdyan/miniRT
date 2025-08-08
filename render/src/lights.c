/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 00:47:11 by saslanya          #+#    #+#             */
/*   Updated: 2025/08/08 13:44:54 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

void	apply_ambient_light(t_rgb *color, t_light *ambient)
{
	color->red *= ambient->ratio * ambient->color.red;
	color->green *= ambient->ratio * ambient->color.green;
	color->blue *= ambient->ratio * ambient->color.blue;
	color->red = fmin(1.0, fmax(0.0, color->red));
	color->green = fmin(1.0, fmax(0.0, color->green));
	color->blue = fmin(1.0, fmax(0.0, color->blue));
}

static void	set_configs(t_light *light, t_hit *hit,
		t_light_config *config, t_vec ray_dir)
{
	t_vec	halfway;

	config->light_dir = normalize(vec_sub(light->pos, hit->point));
	config->view_dir = scalar_product(ray_dir, -1);
	config->diff_intensity = fmax(0.0, dot_product(hit->normal,
				config->light_dir)) * light->ratio;
	halfway = normalize(vec_add(config->view_dir, config->light_dir));
	config->spec_intensity = pow(fmax(dot_product(hit->normal,
					halfway), 0.0), 32) * light->ratio;
}

void	apply_spot_lighting(t_scene *scene, t_hit *hit,
		t_list *light_iter, t_rgb base)
{
	t_light_config	config;
	t_light			*light;

	while (light_iter)
	{
		light = (t_light *)light_iter->content;
		if (!shadow(scene, hit->point, light->pos))
		{
			set_configs(light, hit, &config, normalize(vec_sub(hit->point,
						((t_camera *)scene->cameras->content)->pos)));
			hit->color.red += base.red * light->color.red
				* config.diff_intensity
				+ light->color.red * config.spec_intensity;
			hit->color.green += base.green * light->color.green
				* config.diff_intensity
				+ light->color.green * config.spec_intensity;
			hit->color.blue += base.blue * light->color.blue
				* config.diff_intensity
				+ light->color.blue * config.spec_intensity;
			hit->color.red = fmin(1.0, hit->color.red);
			hit->color.green = fmin(1.0, hit->color.green);
			hit->color.blue = fmin(1.0, hit->color.blue);
		}
		light_iter = light_iter->next;
	}
}
