/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 18:00:00 by drosa-ta          #+#    #+#             */
/*   Updated: 2018/02/05 00:09:54 by drosa-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

bool	init_window(const char *title, SDL_Window **window,
					SDL_Renderer **renderer, SDL_Texture **texture)
{
	bool	success;
	Uint32	pixel_format;

	success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		success = put_error("SDL could not be initialized! SDL_Error: ");
	else
	{
		*window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
									SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (*window == NULL)
			success = put_error("Window could not be created! SDL_Error: ");
		pixel_format = SDL_GetWindowPixelFormat(*window);
		*renderer = SDL_CreateRenderer(
			*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (*renderer == NULL)
			success = put_error("Renderer could not be created! SDL_Error: ");
		*texture = SDL_CreateTexture(*renderer, pixel_format, 0,
									SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	return (success);
}

int		**read_map(char *str, int w, int h)
{
	int	**map;
	int i;
	int j;
	int k;

	if (!str)
		return (NULL);
	map = (int **)malloc(sizeof(*map) * h);
	*map = (int *)malloc(sizeof(**map) * (w * h));
	i = h;
	j = 0;
	k = -1;
	while (--i)
		map[i] = (*map + w * i);
	while (str[0] != '\0' && str[++k])
		if (str[k] != '\n')
			map[i][j++] = (int)(str[k] - '0');
		else
		{
			j = 0;
			i++;
		}
	if (str[0] != '\0' && k != (w * h) + h)
		map = NULL;
	return (map);
}

void	update(SDL_Renderer *renderer, int **world_map, SDL_Texture *texture)
{
	t_ray		ray;
	t_player	player;
	int			x;
	t_line		line;
	Uint32		**buffer;

	buffer = (Uint32 **)read_map("", SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_RenderClear(renderer);
	init_player(&player);
	x = 0;
	while (!done(true, true))
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			ray.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
			ray.length = dist_to_wall(&ray, player, world_map);
			line.height = (int)(SCREEN_HEIGHT / ray.length);
			set_line(&line, ray.is_x_side, world_map[ray.map_x][ray.map_y]);
			draw_pixels(x, line, buffer);
			x++;
		}
		draw_screen(renderer, buffer, texture);
		set_player_pos(&player, world_map);
	}
}

void	end(SDL_Window *window, SDL_Renderer *renderer, int **map)
{
	if (map)
	{
		free(*map);
		free(map);
	}
	else
		write(1, "Map Error!\n", 12);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(1);
}

int		main(int argc, char **argv)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	int				**world_map;
	char			*str;

	window = NULL;
	renderer = NULL;
	world_map = NULL;
	if (argc >= 2)
	{
		str = ft_file_to_str(argv[1]);
		if (str && str[0] == '1')
			world_map = read_map(str, MAP_WIDTH, MAP_HEIGHT);
		free(str);
	}
	if (world_map)
	{
		set_boundary(&world_map[0], MAP_WIDTH, MAP_HEIGHT);
		if (init_window("Wolf3D", &window, &renderer, &texture))
			update(renderer, world_map, texture);
	}
	end(window, renderer, world_map);
	return (0);
}
