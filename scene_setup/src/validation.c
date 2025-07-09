/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:38:22 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/09 17:11:10 by aadyan           ###   ########.fr       */
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
