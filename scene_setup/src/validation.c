/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:38:22 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/07 13:12:02 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
/*
bool	is_valid_f(const char *fname)
{
	const char	*iter;

	iter = ft_strrchr(fname, '.');
	if (iter && !ft_strncmp(iter, FFORMAT, FSIZE))
		return (true);
	else
		return (false);
}
*/

size_t	params_count(const char **params)
{
	size_t	count;

	count = 0;
	while (params && params[count])
		++count;
	return (count);
}

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

bool	params_config(const char **params, size_t mand_count)
{
	if (!params || params_count((const char **)(params + 1)) != mand_count)
		return (false);
	while (*(++params))
	{
		if (!check_param(*params))
			return (false);
	}
	return (true);
}

bool	data_analysis(t_scene *scene)
{
	char	status;
	t_list	*iter;

	status = 0;
	if (scene->camera)
		status |= 1 << 2;
	iter = scene->lights;
	while (iter)
	{
		if (((t_light *)iter->content)->type == LIGHT)
			status |= 1 << 1;
		else if (((t_light *)iter->content)->type == AMBIENT)
			status |= 1;
		iter = iter->next;
	}
	return ((status & 0x07) == 0x07);
}
