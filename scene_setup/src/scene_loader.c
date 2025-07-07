/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:08:37 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/07 12:42:06 by saslanya         ###   ########.fr       */
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

static bool	add_to_list(t_list **list, void *data)
{
	t_list	*new_node;

	if (data)
	{
		new_node = ft_lstnew(data);
		if (!new_node)
			return (free(data), false);
		ft_lstadd_back(list, new_node);
		return (true);
	}
	return (false);
}

static bool	data_addition(const char **params, t_scene *scene
		, t_light *light, t_object *object)
{
	if (**params == CAMERA && !*(*params + 1))
		return (camera_config(params, &(scene->camera)));
	else if (((**params == AMBIENT || **params == LIGHT) && !*(*params + 1))
		&& (light_config(params, &light)
			&& add_to_list(&(scene->lights), light)))
		return (true);
	else if ((!ft_strncmp(*params, "sp", 3) || !ft_strncmp(*params, "pl", 3)
			|| !ft_strncmp(*params, "cy", 3)) && object_config(params, &object)
		&& add_to_list(&(scene->objects), object))
		return (true);
	return (false);
}

static bool	data_read(int fd, t_scene *scene)
{
	char	*line;
	char	**p;
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
		p = ft_split(line, ' ');
		if (!p)
			break ;
		free(line);
		addition_status = data_addition((const char **)p, scene, NULL, NULL);
		free_split(&p);
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
