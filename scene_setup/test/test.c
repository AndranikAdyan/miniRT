#include "scene.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc != 2)
	{
		printf("Usage: %s <scene_file.rt>\n", argv[0]);
		return (1);
	}

	if (!is_valid_f(argv[1]))
	{
		printf("Invalid file format. Expected .rt file.\n");
		return (1);
	}

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
	{
		perror("Memory allocation failed for scene");
		return (1);
	}

	scene->camera = NULL;
	scene->objects = NULL;
	scene->lights = NULL;

	if (!load_scene(argv[1], scene))
	{
		printf("Failed to load scene.\n");
		free_scene(&scene);
		return (1);
	}

	// Вывод информации о камере
	if (scene->camera)
	{
		printf("Camera:\n  pos = (%.2f, %.2f, %.2f)\n  dir = (%.2f, %.2f, %.2f)\n  fov = %d\n",
			scene->camera->pos.x, scene->camera->pos.y, scene->camera->pos.z,
			scene->camera->dir.x, scene->camera->dir.y, scene->camera->dir.z,
			scene->camera->fov);
	}
	else
		printf("No camera found.\n");

	// Вывод информации о источниках света
	t_list	*node = scene->lights;
	while (node)
	{
		t_light *light = (t_light *)node->content;
		printf("Light (type %c):\n  pos = (%.2f, %.2f, %.2f)\n  ratio = %.2f\n  color = (%d,%d,%d)\n",
			light->type,
			light->pos.x, light->pos.y, light->pos.z,
			light->ratio,
			light->color.red, light->color.green, light->color.blue);
		node = node->next;
	}

	// Очистка памяти
	free_scene(&scene);
	return (0);
}

