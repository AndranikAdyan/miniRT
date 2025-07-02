/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_formulas.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:15:33 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/03 01:26:55 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_FORMULAS_H
# define VECTORS_FORMULAS_H

# include "scene.h"

double	dot_product(t_vec a, t_vec b);
t_vec	scalar_product(t_vec a, double num);

#endif