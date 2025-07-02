/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_formulas.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:15:22 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/03 01:37:47 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors_formulas.h"

double	dot_product(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	scalar_product(t_vec a, double num)
{
	t_vec	res;

	res.x = a.x * num;
	res.y = a.y * num;
	res.z = a.z * num;
	return (res);
}

t_vec	cross_product(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x - b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

double	vec_lenght(t_vec a)
{
	return (sqrt(pow(a.x, 2.0) + pow(a.y, 2.0)
			+ pow(a.z, 2.0)));
}

t_vec	normalize(t_vec a)
{
	t_vec	res;
	double	len;

	len = vec_lenght(a);
	res.x = a.x / len;
	res.y = a.y / len;
	res.z = a.z / len;
	return (res);
}
