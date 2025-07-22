/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 01:59:50 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/22 12:38:54 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	free_split(char ***s)
{
	size_t	i;

	i = 0;
	while ((*s)[i])
	{
		free((*s)[i]);
		++i;
	}
	free(*s);
	*s = NULL;
	return ;
}

bool	between_range(double value, double min, double max)
{
	return (value >= min && value <= max);
}

bool	init_vec(const char *s, t_vec *pos, double min, double max)
{
	char	**param;

	param = ft_split(s, ',');
	if (!param || params_count((const char **)param) != VEC_ARG_SIZE)
		return (false);
	pos->x = ft_atof(param[0]);
	pos->y = ft_atof(param[1]);
	pos->z = ft_atof(param[2]);
	free_split(&param);
	if (min != max)
		return (between_range(pos->x, min, max)
			&& between_range(pos->y, min, max)
			&& between_range(pos->z, min, max));
	return (true);
}

bool	init_color(const char *s, t_rgb *color)
{
	char	**param;

	param = ft_split(s, ',');
	if (!param || params_count((const char **)param) != 3)
		return (free_split(&param), false);
	color->red = ft_atof(param[0]);
	color->green = ft_atof(param[1]);
	color->blue = ft_atof(param[2]);
	free_split(&param);
	if (!between_range(color->red, 0.0, 255.0)
		|| !between_range(color->green, 0.0, 255.0)
		|| !between_range(color->blue, 0.0, 255.0))
		return (false);
	color->red = eotf(color->red);
	color->green = eotf(color->green);
	color->blue = eotf(color->blue);
	return (true);
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
