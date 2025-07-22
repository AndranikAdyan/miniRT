/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:02:42 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/22 19:26:20 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "intersection.h"

typedef struct s_hit	t_hit;

typedef struct s_light_config
{
	t_vec	light_dir;
	t_vec	view_dir;
	double	diff_intensity;
	double	spec_intensity;
}	t_light_config;

bool	shadow(t_scene *scene, const t_vec hit_point,
			const t_vec light_pos);
void	apply_ambient_light(t_rgb *color, t_light *ambient);
void	apply_spot_lighting(t_scene *scene, t_hit *hit,
			t_list *light_iter, t_rgb base);

#endif
