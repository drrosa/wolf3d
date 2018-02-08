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

// void verLine(int x, int y1, int y2, const ColorRGB& color)
// {
// 	SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, 255);
// 	SDL_RenderDrawLine(ren, x, y1, x, y2); 
// }

void draw_line(int line_height)
{
    int start;
    int end;

    start = (-line_height / 2) + (SCREEN_HEIGHT / 2);
    if (start < 0)
        start = 0;
    end = (line_height / 2) + (SCREEN_HEIGHT / 2);
    if (end >= SCREEN_HEIGHT)
        end = SCREEN_HEIGHT - 1;
}

void draw_screen(/* const ColorRGB color,*/ SDL_Renderer* renderer)
{
    SDL_RenderPresent(renderer);
    // SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderClear(renderer);
}