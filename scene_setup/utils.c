/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:38:22 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/02 19:40:30 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	is_valid_f(const char *fname)
{
	const char	*iter;

	iter = ft_strrchr(fname, '.');
	if (iter && !ft_strncmp(iter, FFORMAT, FSIZE))
		return (true);
	else
		return (false);
}

void	free_split(char ***s, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free((*s)[i]);
		++i;
	}
	free(*s);
	*s = NULL;
	return ;
}

size_t	params_count(const char **params)
{
	size_t	count;

	count = 0;
	while (params && params[count])
		++count;
	return (count);
}

static bool	check_param(const char *s)
{
	size_t	i;
	bool	is_decimal;

	i = -1;
	is_decimal = false;
	while (s && s[++i])
	{
		if ((s[i] == '-' || s[i] == '+') && i)
			return (false);
		else if (s[i] == '.')
		{
			if (!i || is_decimal)
				return (false);
			is_decimal = true;
		}
		else if (!ft_isdigit(s[i]))
			return (false);
	}
	return (true);
}

bool	params_config(const char **param, size_t mand_count)
{
	if (!params || params_count(params + 1) != mand_count)
		return (false);
	while (++param)
		if (!check_param(param))
			return (false);
	return (true);
}
