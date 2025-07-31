/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:07:31 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/31 14:36:07 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_load.h"

bool	is_valid_f(const char *fname)
{
	const char	*iter;

	iter = ft_strrchr(fname, '.');
	if (iter && !ft_strncmp(iter, FFORMAT, FSIZE))
		return (true);
	else
		return (false);
}

bool	validation(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <scene_file.rt>\n", argv[0]);
		return (false);
	}
	if (!is_valid_f(argv[1]))
	{
		printf("Invalid file format. Expected .rt file.\n");
		return (false);
	}
	return (true);
}
