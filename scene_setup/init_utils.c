/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:28:41 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/02 23:51:08 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	init_vec(const char *s, t_vector *pos)
{
	char	**param;

	param = ft_split(s, ',');
	if (!param || param_count(param) != VEC_ARG_SIZE)
		return (false);
	pos->x = ft_atof(param[0]);
	pos->y = ft_atof(param[1]);
	pos->z = ft_atof(param[2]);
	return (free_split(&param), true);
}

bool	init_color(const char *s, t_rgb *color)
{
	char	**param;

	param = ft_split(s, ',');
	if (!param || param_count(param) != 3)
		return (false);
	color->red = ft_atof(param[0]);
	color->green = ft_atof(param[1]);
	color->blue = ft_atof(param[2]);
	return (free_split(&param), true);
}

double	ft_atof(const char *s)
{
	double	param[4];

	param[0] = 0;
	param[1] = 0;
	param[2] = 0;
	param[3] = 1;
	if (s && *s == '+' || *s == '-')
		param[3] = (double)((*s == '+') - (*s++ == '-'));
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
