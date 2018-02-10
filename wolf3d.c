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
#include <stdio.h>

int world_map[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

bool init_window(bool fullscreen, const char *title, SDL_Window **window,
				 SDL_Renderer **renderer)
{
	SDL_Surface *screenSurface = NULL;
	bool		 success;

	success = true;
	// if (SDL_Init(SDL_INIT_VIDEO) < 0)
	// 	success = put_error("SDL could not be initialized! SDL_Error: ");
	// else
	// {
	*window =
		SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						 SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (*window == NULL)
		success = put_error("Window could not be created! SDL_Error: ");
	*renderer = SDL_CreateRenderer(
		*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (*renderer == NULL)
		success = put_error("Renderer could not be created! SDL_Error: ");
	// SDL_RenderPresent(renderer);
	// else
	// {
	// 	screenSurface = SDL_GetWindowSurface(window);
	// 	SDL_FillRect(screenSurface, NULL,
	// 				 SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	// 	SDL_UpdateWindowSurface(window);
	// 	SDL_Delay(2000);
	// }
	// }
	return (success);
}

bool read_map() { return (true); }

void update(SDL_Renderer *renderer)
{
	t_ray	ray;
	t_player player;
	int		 x;
	int		 wall_height;
	t_line   line;

	init_player(&player);
	// time = 0;
	x = 0;
	// SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	// SDL_RenderDrawLine(renderer, 200, 100, 200, 300);
	// SDL_RenderPresent(renderer);
	while (!done(true, true))
	{
		while (x < SCREEN_WIDTH)
		{
			ray.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
			ray.length = dist_to_wall(&ray, player, world_map);
			line.height = (int)(SCREEN_HEIGHT / ray.length);
			set_line(&line, ray.is_x_side, world_map[ray.map_x][ray.map_y]);
			draw_line(x, line.start, line.end, line.color, renderer);
			x++;
		}
		draw_screen(line.color, renderer);
		x = 0;
		// count_FPS
		set_player_pos(&player, world_map);
	}
}

void end(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	// ft_putendl("Program quit successfully.");
	exit(1);
}

int main(int argc, char *args[])
{
	SDL_Window *  window;
	SDL_Renderer *renderer;

	if (read_map() && init_window(false, "Wolf3D", &window, &renderer))
		update(renderer);
	end(window, renderer);
	return 0;
}

bool put_error(char *str)
{
	perror(str);
	perror(SDL_GetError());
	perror("\n");
	return (false);
}
