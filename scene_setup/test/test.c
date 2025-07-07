#include "scene.h"
#include <stdio.h>
#include <stdlib.h>

static void	print_camera(const t_camera *cam)
{
	if (!cam)
		return ;
	printf("Camera:\n");
	printf("  pos = (%.2f, %.2f, %.2f)\n", cam->pos.x, cam->pos.y, cam->pos.z);
	printf("  dir = (%.2f, %.2f, %.2f)\n", cam->dir.x, cam->dir.y, cam->dir.z);
	printf("  fov = %d\n", cam->fov);
}

static void	print_lights(const t_list *lights)
{
	const t_light	*light;

	while (lights)
	{
		light = (const t_light *)lights->content;
		printf("Light (type %c):\n", light->type);
		printf("  pos = (%.2f, %.2f, %.2f)\n", light->pos.x, light->pos.y, light->pos.z);
		printf("  ratio = %.2f\n", light->ratio);
		printf("  color = (%d, %d, %d)\n", light->color.red, light->color.green, light->color.blue);
		lights = lights->next;
	}
}

static void	print_objects(const t_list *objects)
{
	const t_object	*obj;

	while (objects)
	{
		obj = (const t_object *)objects->content;
		if (obj->type == SPHERE)
		{
			printf("Sphere:\n");
			printf("  pos = (%.2f, %.2f, %.2f)\n", obj->variant.sphere.pos.x,
				obj->variant.sphere.pos.y, obj->variant.sphere.pos.z);
			printf("  radius = %.2f\n", obj->variant.sphere.radius);
			printf("  color = (%d, %d, %d)\n", obj->variant.sphere.color.red,
				obj->variant.sphere.color.green, obj->variant.sphere.color.blue);
		}
		else if (obj->type == PLANE)
		{
			printf("Plane:\n");
			printf("  pos = (%.2f, %.2f, %.2f)\n", obj->variant.plane.pos.x,
				obj->variant.plane.pos.y, obj->variant.plane.pos.z);
			printf("  normal = (%.2f, %.2f, %.2f)\n", obj->variant.plane.normal.x,
				obj->variant.plane.normal.y, obj->variant.plane.normal.z);
			printf("  color = (%d, %d, %d)\n", obj->variant.plane.color.red,
				obj->variant.plane.color.green, obj->variant.plane.color.blue);
		}
		else if (obj->type == CYLINDER)
		{
			printf("Cylinder:\n");
			printf("  pos = (%.2f, %.2f, %.2f)\n", obj->variant.cylinder.pos.x,
				obj->variant.cylinder.pos.y, obj->variant.cylinder.pos.z);
			printf("  dir = (%.2f, %.2f, %.2f)\n", obj->variant.cylinder.dir.x,
				obj->variant.cylinder.dir.y, obj->variant.cylinder.dir.z);
			printf("  radius = %.2f\n", obj->variant.cylinder.radius);
			printf("  height = %.2f\n", obj->variant.cylinder.height);
			printf("  color = (%d, %d, %d)\n", obj->variant.cylinder.color.red,
				obj->variant.cylinder.color.green, obj->variant.cylinder.color.blue);
		}
		else
			printf("Unknown object type '%c'\n", obj->type);
		objects = objects->next;
	}
}

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

	if (!load_scene(argv[1], scene))
	{
		printf("Failed to load scene.\n");
		free_scene(&scene);
		return (1);
	}

	print_camera(scene->camera);
	print_lights(scene->lights);
	print_objects(scene->objects);

	free_scene(&scene);
	return (0);
}

