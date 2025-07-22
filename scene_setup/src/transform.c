/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:46:25 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/22 12:39:29 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

double	eotf(double val)
{
	val /= 255.0;
	if (val <= 0.04045)
		return (val / 12.92);
	else
		return (pow((val + 0.055) / 1.055, 2.4));
}

double	oetf(double val)
{
	if (val <= 0.0031308)
		return (val * 12.92);
	else
		return (1.055 * pow(val, 1.0 / 2.4) - 0.055);
}

int	linear_to_gammaint(t_rgb *color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(fmin(1.0, fmax(0.0, color->red)) * 255.0 + 0.5);
	g = (int)(fmin(1.0, fmax(0.0, color->green)) * 255.0 + 0.5);
	b = (int)(fmin(1.0, fmax(0.0, color->blue)) * 255.0 + 0.5);
	return ((r << 16) | (g << 8) | b);
}
