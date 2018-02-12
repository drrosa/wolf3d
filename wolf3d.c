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

bool	init_window(bool fullscreen, const char *title, SDL_Window **window,
					SDL_Renderer **renderer)
{
	bool	success;

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
		*renderer = SDL_CreateRenderer(
			*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (*renderer == NULL)
			success = put_error("Renderer could not be created! SDL_Error: ");
	}
	return (success);
}

int		**read_map(char *str)
{
	int	**map;
	int i;
	int j;
	int k;

	if (!str)
		return (0);
	map = (int **)malloc(sizeof(*map) * MAP_HEIGHT);
	*map = (int *)malloc(sizeof(**map) * (MAP_WIDTH * MAP_HEIGHT));
	i = MAP_HEIGHT;
	j = 0;
	k = -1;
	while (--i)
		map[i] = (*map + MAP_WIDTH * i);
	while (str[++k])
		if (str[k] != '\n')
			map[i][j++] = (int)(str[k] - '0');
		else
		{
			j = 0;
			i++;
		}
	free(str);
	return (map);
}

void	update(SDL_Renderer *renderer, int **world_map)
{
	t_ray		ray;
	t_player	player;
	int			x;
	int			wall_height;
	t_line		line;

	SDL_RenderClear(renderer);
	init_player(&player);
	x = 0;
	while (!done(true, true))
	{
		while (x < SCREEN_WIDTH)
		{
			ray.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
			ray.length = dist_to_wall(&ray, player, world_map);
			line.height = (int)(SCREEN_HEIGHT / ray.length);
			set_line(&line, ray.is_x_side, world_map[ray.map_x][ray.map_y]);
			draw_line(x, line, renderer);
			x++;
		}
		draw_screen(line.color, renderer);
		x = 0;
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
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(1);
}

int		main(int argc, char **argv)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				**world_map;

	if (argc > 1 && (world_map = read_map(ft_file_to_str(argv[1]))))
		if (init_window(false, "Wolf3D", &window, &renderer))
			update(renderer, world_map);
	end(window, renderer, world_map);
	return (0);
}
