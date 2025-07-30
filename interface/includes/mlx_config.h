/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_config.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:30:26 by saslanya          #+#    #+#             */
/*   Updated: 2025/07/30 23:21:14 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_CONFIG_H
# define MLX_CONFIG_H

# include <stdbool.h>
# include <X11/keysym.h>
# include "mlx.h"
# include "scene.h"           // для t_scene
# include "intersection.h"    

# define WIN_WEIGHT 1080
# define WIN_HEIGHT 720
# define THREADS_SIZE 4 // 16 is more stable and faster
# define STEP 0.2

# define PLUS 61
# define PLUS2 65451
# define MINUS 45
# define MINUS2 65453

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mlx
{
	void		*mlx;
	void		*window;
	t_data		*img_data;
	t_scene		*scene;
}	t_mlx;

t_mlx	*init_mlx(char **argv);
int		free_mlx(t_mlx *mlx);
int		keys_handle(int keycode, t_mlx *mlx);
int		mouse_click(int button, int x, int y, void *param);
bool	multi_rendering(t_mlx *mlx, int i);

#endif
