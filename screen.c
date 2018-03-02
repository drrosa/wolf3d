/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 00:19:38 by drosa-ta          #+#    #+#             */
/*   Updated: 2018/02/08 00:19:40 by drosa-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	get_frametime(void)
{
	static unsigned long prev_ticks;
	static unsigned long ticks;

	prev_ticks = ticks;
	ticks = SDL_GetTicks();
	return ((ticks - prev_ticks) / 1000.0);
}

void	draw_pixels(int x, t_line line, Uint32 **buffer)
{
	while (line.start < line.end)
		buffer[line.start++][x] = line.color;
}

void	set_wall_colors(Uint32 color[5], bool is_x_side)
{
	int color_brightness;

	if (!is_x_side)
		color_brightness = 127;
	else
		color_brightness = 255;
	color[1] = color_brightness << 16;
	color[2] = color_brightness << 8;
	color[3] = color_brightness;
	color[4] = color[1] | color[2] | color[3];
	color[0] = color[1] | color[2];
}

void	set_line(t_line *line, bool is_x_side, int wall)
{
	Uint32 color[5];

	set_wall_colors(color, is_x_side);
	line->start = (-line->height / 2) + (SCREEN_HEIGHT / 2);
	if (line->start < 0)
		line->start = 0;
	line->end = (line->height / 2) + (SCREEN_HEIGHT / 2);
	if (line->end >= SCREEN_HEIGHT)
		line->end = SCREEN_HEIGHT - 1;
	line->color = color[wall];
}

void	draw_screen(SDL_Renderer *renderer, Uint32 **buffer, SDL_Texture *tex)
{
	int y;
	int x;

	x = 0;
	y = 0;
	SDL_UpdateTexture(tex, NULL, *buffer, (SCREEN_WIDTH) * sizeof(Uint32));
	SDL_RenderCopy(renderer, tex, NULL, NULL);
	while (x < SCREEN_WIDTH)
	{
		while (y < SCREEN_HEIGHT)
		{
			if (y > SCREEN_HEIGHT / 2)
				buffer[y][x] = 0x00654321;
			else if (y < SCREEN_HEIGHT / 2)
				buffer[y][x] = 0x00add8e6;
			else
				buffer[y][x] = 0;
			y++;
		}
		y = 0;
		x++;
	}
	SDL_RenderPresent(renderer);
}
