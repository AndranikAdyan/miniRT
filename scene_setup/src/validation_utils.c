/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:01:33 by aadyan            #+#    #+#             */
/*   Updated: 2025/07/09 17:03:04 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

size_t	params_count(const char **params)
{
	size_t	count;

	count = 0;
	while (params && params[count])
		++count;
	return (count);
}

bool	is_valid_f(const char *fname)
{
	const char	*iter;

	iter = ft_strrchr(fname, '.');
	if (iter && !ft_strncmp(iter, FFORMAT, FSIZE))
		return (true);
	else
		return (false);
}
