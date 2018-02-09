/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 00:19:47 by drosa-ta          #+#    #+#             */
/*   Updated: 2018/02/08 00:19:48 by drosa-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void init_player(t_player *player)
{
	player->pos_x = 22;
	player->pos_y = 12;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
}

bool keyDown(SDL_Scancode key)
{
	return (SDL_GetKeyboardState(NULL)[key] != 0);
}

void get_player_pos(t_player player) {}

// Returns 1 if you close the window or press the escape key.
// Also handles everything thats needed per frame.
bool done(bool quit_if_esc, bool delay)
{
	SDL_Event event;
	if (delay)
		SDL_Delay(5); // So it consumes less processing power

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return true;
		if (quit_if_esc && keyDown(SDL_SCANCODE_ESCAPE))
			return true;
	}
	return false;
}
