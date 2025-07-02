/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 01:19:48 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/02 19:41:58 by saslanya         ###   ########.fr       */
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
# define VEC_ARG_SIZE

void	free_split(char ***s, size_t count);
bool	is_valid_f(const char *fname);
bool	params_config(const char **param, size_t mand_count);
double	ft_atof(const char *arg);

#endif
