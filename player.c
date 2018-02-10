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

double get_frametime()
{
	static unsigned long prev_ticks;
	static unsigned long ticks;

	prev_ticks = ticks;
	ticks = SDL_GetTicks();
	return ((ticks - prev_ticks) / 1000.0);
}

void move_forward(t_player *player, int world_map[24][24])
{
	if (!world_map[(int)(player->pos_x + player->dir_x * player->move_speed)]
				  [(int)player->pos_y])
		player->pos_x += player->dir_x * player->move_speed;
	if (!world_map[(int)player->pos_x]
				  [(int)(player->pos_y + player->dir_y * player->move_speed)])
		player->pos_y += player->dir_y * player->move_speed;
}

void move_backward(t_player *player, int world_map[24][24])
{
	if (!world_map[(int)(player->pos_x - player->dir_x * player->move_speed)]
				  [(int)player->pos_y])
		player->pos_x -= player->dir_x * player->move_speed;
	if (!world_map[(int)player->pos_x]
				  [(int)(player->pos_y - player->dir_y * player->move_speed)])
		player->pos_y -= player->dir_y * player->move_speed;
}

void look_right(t_player *player, int world_map[24][24])
{
	// both camera direction and camera plane must be rotated
	double oldDirX = player->dir_x;
	player->dir_x = player->dir_x * cos(-player->rot_speed) -
					player->dir_y * sin(-player->rot_speed);
	player->dir_y = oldDirX * sin(-player->rot_speed) +
					player->dir_y * cos(-player->rot_speed);
	double oldPlaneX = player->plane_x;
	player->plane_x = player->plane_x * cos(-player->rot_speed) -
					  player->plane_y * sin(-player->rot_speed);
	player->plane_y = oldPlaneX * sin(-player->rot_speed) +
					  player->plane_y * cos(-player->rot_speed);
}

void look_left(t_player *player, int world_map[24][24])
{
	// both camera direction and camera plane must be rotated
	double oldDirX = player->dir_x;
	player->dir_x = player->dir_x * cos(player->rot_speed) -
					player->dir_y * sin(player->rot_speed);
	player->dir_y = oldDirX * sin(player->rot_speed) +
					player->dir_y * cos(player->rot_speed);
	double oldPlaneX = player->plane_x;
	player->plane_x = player->plane_x * cos(player->rot_speed) -
					  player->plane_y * sin(player->rot_speed);
	player->plane_y = oldPlaneX * sin(player->rot_speed) +
					  player->plane_y * cos(player->rot_speed);
}

void set_player_pos(t_player *player, int world_map[24][24])
{
	double frame_time;

	frame_time = get_frametime();
	player->move_speed = frame_time * 5.0;
	player->rot_speed = frame_time * 3.0;

	if (is_input_key(SDLK_UP))
		move_forward(player, world_map);
	if (is_input_key(SDLK_DOWN))
		move_backward(player, world_map);
	if (is_input_key(SDLK_RIGHT))
		look_right(player, world_map);
	if (is_input_key(SDLK_LEFT))
		look_left(player, world_map);
}
