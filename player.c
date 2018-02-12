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

void	move_forward(t_player *player, int **world_map)
{
	if (!world_map[(int)(player->pos_x + player->dir_x * player->move_speed)]
					[(int)player->pos_y])
		player->pos_x += player->dir_x * player->move_speed;
	if (!world_map[(int)player->pos_x]
					[(int)(player->pos_y + player->dir_y * player->move_speed)])
		player->pos_y += player->dir_y * player->move_speed;
}

void	move_backward(t_player *player, int **world_map)
{
	if (!world_map[(int)(player->pos_x - player->dir_x * player->move_speed)]
					[(int)player->pos_y])
		player->pos_x -= player->dir_x * player->move_speed;
	if (!world_map[(int)player->pos_x]
					[(int)(player->pos_y - player->dir_y * player->move_speed)])
		player->pos_y -= player->dir_y * player->move_speed;
}

void	look_right(t_player *player)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(-player->rot_speed) -
					player->dir_y * sin(-player->rot_speed);
	player->dir_y = old_dir_x * sin(-player->rot_speed) +
					player->dir_y * cos(-player->rot_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(-player->rot_speed) -
						player->plane_y * sin(-player->rot_speed);
	player->plane_y = old_plane_x * sin(-player->rot_speed) +
						player->plane_y * cos(-player->rot_speed);
}

void	look_left(t_player *player)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(player->rot_speed) -
					player->dir_y * sin(player->rot_speed);
	player->dir_y = old_dir_x * sin(player->rot_speed) +
					player->dir_y * cos(player->rot_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(player->rot_speed) -
						player->plane_y * sin(player->rot_speed);
	player->plane_y = old_plane_x * sin(player->rot_speed) +
						player->plane_y * cos(player->rot_speed);
}

void	set_player_pos(t_player *player, int **world_map)
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
		look_right(player);
	if (is_input_key(SDLK_LEFT))
		look_left(player);
}
