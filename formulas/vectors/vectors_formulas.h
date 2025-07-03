/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_formulas.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:15:33 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/03 13:30:18 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_FORMULAS_H
# define VECTORS_FORMULAS_H

# include "scene.h"

double	dot_product(t_vec *a, t_vec *b);
t_vec	scalar_product(t_vec *a, double num);
t_vec	cross_product(t_vec *a, t_vec *b);
double	vec_length(t_vec *a);
t_vec	normalize(t_vec *a);

#endif