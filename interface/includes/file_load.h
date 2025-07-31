/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_load.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:10:17 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/31 14:39:49 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_LOAD_H
# define FILE_LOAD_H

# include "mlx_config.h"

bool	is_valid_f(const char *fname);
bool	validation(int argc, char **argv);
void	init_textures(t_mlx *mlx);

#endif
