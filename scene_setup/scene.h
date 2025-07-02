/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 01:19:48 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/02 23:52:35 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"

# define FFORMAT ".rt"
# define FSIZE 4
# define CAM_ARG_SIZE 3
# define VEC_ARG_SIZE 3

void	free_split(char ***s);
bool	is_valid_f(const char *fname);
bool	init_vec(const char *s, t_vector *pos);
bool	init_color(const char *s, t_rgb *color);
bool	params_config(const char **param, size_t mand_count);
double	ft_atof(const char *arg);

#endif
