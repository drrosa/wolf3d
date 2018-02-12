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

void	draw_line(int x, t_line line, SDL_Renderer *renderer)
{
	t_color color;

	color = line.color;
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
	while (line.start < line.end)
	{
		SDL_RenderDrawPoint(renderer, x, line.start++);
	}
}

void	set_wall_colors(t_color color[5])
{
	color[1] = (struct s_color){255, 0, 0};
	color[2] = (struct s_color){0, 255, 0};
	color[3] = (struct s_color){0, 0, 255};
	color[4] = (struct s_color){255, 255, 255};
	color[0] = (struct s_color){255, 255, 0};
}

void	set_line(t_line *line, bool is_x_side, int wall)
{
	t_color color[5];
	t_color wall_color;

	set_wall_colors(color);
	line->start = (-line->height / 2) + (SCREEN_HEIGHT / 2);
	if (line->start < 0)
		line->start = 0;
	line->end = (line->height / 2) + (SCREEN_HEIGHT / 2);
	if (line->end >= SCREEN_HEIGHT)
		line->end = SCREEN_HEIGHT - 1;
	line->color = color[wall];
	if (!is_x_side)
	{
		line->color.r /= 2;
		line->color.b /= 2;
		line->color.g /= 2;
	}
}

void	draw_screen(t_color color, SDL_Renderer *renderer)
{
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}
