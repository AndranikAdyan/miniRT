/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:08:37 by saslanya          #+#    #+#             */
/*   Updated: 2025/08/08 11:26:04 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	free_scene(t_scene **scene)
{
	t_list	*iter;

	if (!*scene)
		return ;
	ft_lstclear(&((*scene)->cameras), free);
	free((*scene)->ambient);
	if ((*scene)->objects)
	{
		iter = (*scene)->objects;
		while (iter)
		{
			if (((t_object *)iter->content)->type == SPHERE)
			{
				free(((t_object *)iter->content)->variant.sphere.format);
				free(((t_object *)iter->content)->variant.sphere.bformat);
			}
			iter = iter->next;
		}
	}
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
	t_camera	*camera;

	camera = NULL;
	if (**params == CAMERA && !*(*params + 1) && camera_config(params, &camera))
		return (add_to_list(&(scene->cameras), camera));
	else if (((**params == AMBIENT || **params == LIGHT) && !*(*params + 1))
		&& (light_config(params, &light)))
	{
		if (**params == AMBIENT)
		{
			if (scene->ambient)
				return (false);
			return (scene->ambient = light, true);
		}
		return (add_to_list(&(scene->lights), light));
	}
	else if (object_config(params, &object)
		&& add_to_list(&(scene->objects), object))
		return (true);
	return (free(object), false);
}

static bool	data_read(int fd, t_scene *scene, char *line)
{
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
		if (ft_strchr(line, NEWLINE))
			*ft_strrchr(line, NEWLINE) = ' ';
		p = ft_split(line, ' ');
		if (!p)
			break ;
		free(line);
		addition_status = data_addition((const char **)p, scene, NULL, NULL);
		free_split(&p);
		if (!addition_status)
			return (false);
	}
	return (free(line), data_analysis(scene));
}

bool	load_scene(const char *filename, t_scene *scene)
{
	bool	status;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (false);
	status = data_read(fd, scene, NULL);
	close(fd);
	return (status);
}
