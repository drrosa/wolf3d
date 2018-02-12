#ifndef WOLF3D_H
#define WOLF3D_H
#include <SDL2/SDL.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define BUFF_SIZE 4096

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double move_speed;
	double rot_speed;
} t_player;

typedef struct s_ray
{
	double camera_x;
	double dir_x;
	double dir_y;
	int	map_x;
	int	map_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	bool   is_x_side;
	int	step_x;
	int	step_y;
	double length;
} t_ray;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_line
{
	int		height;
	int		start;
	int		end;
	t_color color;
} t_line;

void   init_player(t_player *player);
double dist_to_wall(t_ray *ray, t_player player, int **world_map);
void   set_line(t_line *line, bool is_x_side, int wall);
void   draw_line(int x, t_line line, SDL_Renderer *renderer);
void   draw_screen(t_color color, SDL_Renderer *renderer);
void   set_player_pos(t_player *player, int **world_map);
bool   put_error(char *str);
bool   is_input_key(SDL_Keycode key);
bool   done(bool quit_if_esc, bool delay);
char * ft_file_to_str(const char *file_name);
double get_frametime(void);
#endif
