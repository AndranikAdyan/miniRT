/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 01:59:50 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/04 11:58:50 by saslanya         ###   ########.fr       */
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

bool	init_vec(const char *s, t_vec *pos)
{
	char	**param;

	param = ft_split(s, ',');
	if (!param || params_count((const char **)param) != VEC_ARG_SIZE)
		return (false);
	pos->x = ft_atof(param[0]);
	pos->y = ft_atof(param[1]);
	pos->z = ft_atof(param[2]);
	return (free_split(&param), true);
}

bool	init_color(const char *s, t_rgb *color)
{
	char	**param;
	int		value[3];
	bool	values_status;

	param = ft_split(s, ',');
	if (!param || params_count((const char **)param) != 3)
		return (false);
	value[0] = ft_atoi(param[0]);
	value[1] = ft_atoi(param[1]);
	value[2] = ft_atoi(param[2]);
	values_status = (value[0] >= 0 && value[0] <= UCHAR_MAX)
		&& (value[1] >= 0 && value[1] <= UCHAR_MAX)
		&& (value[2] >= 0 && value[2] <= UCHAR_MAX);
	if (values_status)
	{
		color->red = value[0];
		color->green = value[1];
		color->blue = value[2];
	}
	return (free_split(&param), values_status);
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
