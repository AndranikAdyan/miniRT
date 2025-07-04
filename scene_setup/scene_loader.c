/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:08:37 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/04 13:11:17 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	free_scene(t_scene **scene)
{
	free((*scene)->camera);
	ft_lstclear(&((*scene)->objects), free);
	ft_lstclear(&((*scene)->lights), free);
	free(*scene);
	*scene = NULL;
}

static bool	data_addition(const char **params, t_scene *scene, t_light *light)
{
	t_list	*node;

	if (**params == CAMERA && !*(*params + 1))
		return (camera_config(params, &(scene->camera)));
	else if ((**params == AMBIENT || **params == LIGHT) && !*(*params + 1))
	{
		if (light_config(params, &light))
		{
			node = ft_lstnew(light);
			if (node)
				return (ft_lstadd_back(&(scene->lights), node), true);
		}
		return (free(light), false);
	}
	return (false);
}

static bool	data_read(int fd, t_scene *scene)
{
	char	*line;
	char	**params;
	bool	addition_status;

	while (true)
	{
		line = get_next_line(fd);
		if (!line || !*line)
			break ;
		if (*line == NEWLINE || *line == '#')
		{
			free(line);
			continue ;
		}
		*(ft_strchr(line, NEWLINE)) = ' ';
		params = ft_split(line, ' ');
		if (!params)
			break ;
		free(line);
		addition_status = data_addition((const char **)params, scene, NULL);
		free_split(&params);
		if (!addition_status)
			return (false);
	}
//	return (free(line), data_analysis(scene));
	return (free(line), true);
}

bool	load_scene(const char *filename, t_scene *scene)
{
	bool	status;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (false);
	status = data_read(fd, scene);
	close(fd);
	return (status);
}
