/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_basic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:15:18 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/09 17:12:07 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors_formulas.h"

double	vec_length(t_vec a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec	normalize(t_vec a)
{
	t_vec	res;
	double	len;

	len = vec_length(a);
	if (len == 0)
		return ((t_vec){0, 0, 0});
	res.x = a.x / len;
	res.y = a.y / len;
	res.z = a.z / len;
	return (res);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}
