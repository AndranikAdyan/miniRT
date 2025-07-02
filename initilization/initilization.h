/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilization.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:46:08 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/03 00:11:25 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITILIZATION_H
# define INITILIZATION_H

# include "miniRT.h"

typedef struct s_mlx    t_mlx;

t_mlx   *init_mlx(void);
int     free_mlx(t_mlx *mlx);

#endif
