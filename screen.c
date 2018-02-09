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

// void pset(int x, int y, const ColorRGB& color)
// {
//   SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, 255);
//   SDL_RenderDrawPoint(ren, x, y);
// }

void draw_line(int x, int y1, int y2, const t_color color,
			   SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
	SDL_RenderDrawLine(renderer, x, y1, x, y2);
}

void set_wall_colors(t_color color[5])
{
	/*Red*/
	color[1] = (struct s_color){255, 0, 0};
	/*Green*/
	color[2] = (struct s_color){0, 255, 0};
	/*Blue*/
	color[3] = (struct s_color){0, 0, 255};
	/*White*/
	color[4] = (struct s_color){255, 255, 255};
	/*Yellow*/
	color[0] = (struct s_color){255, 255, 0};
}

void set_line(t_line *line, bool is_x_side, int wall)
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

void draw_screen(t_color color, SDL_Renderer *renderer)
{
	SDL_RenderPresent(renderer);
	// Black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}
