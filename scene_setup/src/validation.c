/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:38:22 by saslanya          #+#    #+#             */
/*   Updated: 2025/08/09 17:54:40 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	check_letter(const char *s, int i, bool *is_decimal)
{
	if (s[i] == '-' || s[i] == '+')
	{
		if (!ft_isdigit(s[i + 1]))
			return (false);
	}
	else if (s[i] == '.')
	{
		if (!i || *is_decimal)
			return (false);
		*is_decimal = true;
	}
	else if (s[i] == ',')
	{
		if (!i || !ft_isdigit(s[i - 1]) || (!ft_isdigit(s[i + 1])
				&& s[i + 1] != '+' && s[i + 1] != '-'))
			return (false);
		*is_decimal = false;
	}
	else if (!ft_isdigit(s[i]))
		return (false);
	return (true);
}

static bool	check_param(const char *s)
{
	size_t	i;
	bool	is_decimal;

	i = -1;
	is_decimal = false;
	while (s && s[++i])
		if (!check_letter(s, i, &is_decimal))
			return (false);
	return (true);
}

size_t	params_count(const char **params)
{
	size_t	count;

	count = 0;
	while (params && params[count])
		++count;
	return (count);
}

bool	params_config(const char **params, size_t mand_count)
{
	size_t	count;

	if (!params)
		return (false);
	count = params_count((const char **)(params + 1));
	if (!ft_strncmp(*params, "sp", 3) && count > mand_count)
	{
		if (check_xpm(params[4]) && (count == 4
				|| (count == 5 && check_xpm(params[5]))))
			count -= 1 + (count == 5);
		else
			return (false);
	}
	if (count != mand_count)
		return (false);
	while (--count)
	{
		if (!check_param(params[count]))
			return (false);
	}
	return (true);
}

bool	data_analysis(t_scene *scene)
{
	char	status;

	status = 0;
	if (scene->cameras)
		status |= 1 << 2;
	if (scene->ambient)
		status |= 1;
	if (scene->lights)
		status |= 1 << 1;
	return ((status & 0x07) == 0x07);
}
