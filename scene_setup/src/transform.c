/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:46:25 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/31 14:44:47 by saslanya         ###   ########.fr       */
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

double	ft_atof(const char *s)
{
	double	param[4];

	param[0] = 0;
	param[1] = 0;
	param[2] = 0;
	param[3] = 1;
	if (s && (*s == '+' || *s == '-') && ++s)
		param[3] = (double)((*(s - 1) == '+') - (*(s - 1) == '-'));
	while (s && *s)
	{
		if (ft_isdigit(*s))
		{
			param[0] = param[0] * 10.0 + (double)(*s - '0');
			if (param[2])
				++param[1];
		}
		else if (*s == '.' && !param[2])
			param[2] = 1.0;
		else
			return (0.0);
		++s;
	}
	param[0] *= param[3];
	return (param[0] / pow(10.0, (int)param[1]));
}

bool	check_xpm(const char *file)
{
	char	*format;

	if (!file)
		return (false);
	format = ft_strrchr(file, '.');
	if (format)
		return (!ft_strncmp(format, XPM_F, XPM_S));
	return (false);
}
